/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 12:05:30 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/23 19:33:53 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include "../../inc/signals.h"

static int	heredoc_init(char **delimiter, int **fd, t_token *tok, t_tree *tree)
{
	int	fd_new;

	if (tok->quote_type == QUO_DEFAULT)
		tok->expand = true;
	if (!ft_superstrndup(delimiter, (char *)tok->tok_chars->data,
			tok->tok_chars->len, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_reset(tok->tok_chars))
		exit_parser(tree, MSG_UNINTAL);
	fd_new = open("/tmp/heredoc_tmp",
			O_WRONLY | O_APPEND | O_CREAT | O_EXCL, FILE_ACCESS);
	if (fd_new < 0)
		exit_parser(tree, MSG_OPENERR);
	vec_push(tree->fds, &fd_new);
	*fd = vec_get(tree->fds, tree->fds->len - 1);
	// ft_printf("\ninit(): ");
	// vec_putvars(tree->fds);
	return (SUCCESS);
}

static int	heredoc_reset(t_tree *tree, char **line)
{
	(void)tree;
	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	return (SUCCESS);
}

static int	tokenise_heredoc(t_token *tok, int fd, t_tree *tree)
{
	char	*line;
	t_vec	*tmp;

	tmp = NULL;
	if (!vec_new(tok->tok_chars, 1, sizeof(char))
		|| !vec_alloc(&tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	while (1)
	{
		line = gnl(fd);
		if (!line)
		{
			vec_trim(tok->tok_chars, tok->tok_chars->len - 1, 1);
			free(line);
			return (SUCCESS);
		}
		if (!vec_from(tmp, line, ft_strlen(line), sizeof(char))
			|| !vec_append(tok->tok_chars, tmp))
			exit_parser(tree, MSG_MALLOCF);
		if (!vec_reset(tmp))
			exit_parser(tree, MSG_UNINTAL);
		free(line);
	}
}

static int	heredoc_exit(int fd, t_tree *tree)
{
	if (fd)
		if (close(fd) < 0 || unlink("/tmp/heredoc_tmp") < 0)
			exit_parser(tree, MSG_ACCESSF);
	// heredoc_signals_hook(TURN_OFF);
	// readline_signals_hook(TURN_ON);
	return (SUCCESS);
}

static int	ms_history_append(t_token *tok, char *line, t_tree *tree)
{
	t_vec	*tmp_a;
	t_vec	*tmp_b;
	char	nl;

	tmp_a = NULL;
	tmp_b = NULL;
	nl = '\n';
	if (!vec_alloc(&tmp_a, tree->a_buf)
		|| !vec_alloc(&tmp_b, tree->a_buf)
		|| !vec_new(tmp_a, 0, sizeof(char))
		|| !vec_append(tmp_a, tok->tok_chars))
		exit_parser(tree, MSG_MALLOCF);
	if (line)
		if (!vec_push(tmp_a, &nl)
			|| !vec_from(tmp_b, line, ft_strlen(line), sizeof(char))
			|| !vec_append(tmp_a, tmp_b))
		exit_parser(tree, MSG_MALLOCF);
	if (!ft_superstrndup(&tok->heredoc, (char *)tmp_a->data,
		tmp_a->len, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	return (SUCCESS);
}

static int	heredoc_reopen(int **fd, t_tree *tree)
{
	int	fd_old;
	int	fd_new;

	fd_old = 0;
	vec_pop(&fd_old, tree->fds);
	if (close(fd_old) < 0)
		exit_parser(tree, MSG_ACCESSF);
	fd_new = open("/tmp/heredoc_tmp", O_RDONLY);
	if (fd_new < 0)
		exit_parser(tree, MSG_ACCESSF);
	vec_push(tree->fds, &fd_new);
	*fd = vec_get(tree->fds, tree->fds->len - 1);
	return (SUCCESS);
}

int	heredoc_clean_exit(t_token *tok, char *line, t_tree *tree)
{
	int	*fd;

	fd = NULL;
	if (!heredoc_reopen(&fd, tree)
		|| !tokenise_heredoc(tok, *fd, tree)
		|| !ms_history_append(tok, line, tree)
		|| !heredoc_reset(tree, &line)
		|| !heredoc_exit(*fd, tree))
		return (FAIL);
	rl_clear_history();
	return (SUCCESS);
}

int	heredoc_dirty_exit(t_tree *tree)
{
	int	fd;

	// ft_printf("I got here\n");
	// ft_printf("\ndirty(): ");
	// vec_putvars(tree->fds);
	if (tree->fds->len > 0)
	{
		vec_pop(&fd, tree->fds);
		if (close(fd) < 0 || unlink("/tmp/heredoc_tmp") < 0)
			exit_parser(tree, MSG_ACCESSF);
	}
	if (unlink("/tmp/heredoc_tmp") < 0)
		exit_parser(tree, MSG_ACCESSF);
	return (SUCCESS);
}

int	heredoc(t_token *tok, t_tree *tree)
{
	char	*line;
	char	*delimiter;
	int		*fd;

	line = NULL;
	delimiter = NULL;
	fd = NULL;
	if (!tok->tok_chars || !heredoc_init(&delimiter, &fd, tok, tree))
		return (FAIL);
	// ft_printf("\nheredoc(): ");
	// vec_putvars(tree->fds);
	while (1)
	{
		heredoc_reset(tree, &line);
		line = readline("> ");
		if (line && ft_strlen(line) == 0)
			continue ;
		else if (line == NULL || ft_strcmp(line, delimiter) == 0)
			return (heredoc_clean_exit(tok, line, tree));
		ft_putendl_fd(line, *fd);
	}
}

		// if (g_receipt == EXIT_CTRLC)
		// 	return (heredoc_dirty_exit(*fd, line, tree));

int	heredoc_fork(t_token *tok, t_tree *tree)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		heredoc_signals_hook(TURN_ON);
		if (!heredoc(tok, tree))
			return (FAIL);
		heredoc_signals_hook(TURN_OFF);
		exit(0);
	}
	else
	{
		readline_signals_hook(TURN_OFF);
		pid = wait(&status);
		if (WIFEXITED(status))
			ft_printf("Exit ended\n");
		if (WIFSIGNALED(status))
			ft_printf("Signal ended\n");
		if (g_receipt == EXIT_CTRLC)
			heredoc_dirty_exit(tree);
		readline_signals_hook(TURN_ON);
	}
	if (pid < 0)
		perror("in fork();");
	return (SUCCESS);
}

// int	heredoc_handler(t_token *tok, t_tree *tree)
// {
// 	if (!heredoc_fork(tok, tree))
// 		return (FAIL);
// 	if (g_receipt == EXIT_CTRLC)
// 	{
// 		// ft_printf("g_receipt is: %d\n", g_receipt);
// 		return (heredoc_dirty_exit(tree));
// 	}
// 	readline_signals_hook(TURN_ON);
// 	return (SUCCESS);
// }
