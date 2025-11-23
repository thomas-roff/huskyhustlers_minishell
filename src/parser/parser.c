/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:21 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/23 18:53:39 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"
#include <readline/history.h>

static void	tok_init(t_token **tok, t_vec *tokens, t_tree *tree);
static bool	ft_nothingtodo(char **line);
static int	lexer_init(t_vec **tokens, t_vec **linec, char *line, t_tree *tree);
static void	ft_rl_append(t_vec *linec, t_token *tok, char *line, t_tree *tree);
static void	ft_add_history(char **line, t_vec *linec, t_tree *tree);

int	parser(t_tree *tree, char **line, t_flag mode_flag)
{
	t_vec		*toks;
	t_token		*tok;
	t_vec		*linec;
	char		*linep;
	t_redirect	rdr_flag;

	toks = NULL;
	tok = NULL;
	linec = NULL;
	linep = *line;
	if (!tree || !valid_input(*line) || !lexer_init(&toks, &linec, *line, tree))
		return (FAIL);
	if (ft_nothingtodo(line))
		return (SUCCESS);
	rdr_flag = RDR_DEFAULT;
	while (*linep)
	{
		tok_init(&tok, toks, tree);
		tokenise(tok, &rdr_flag, linep, tree);
		ft_rl_append(linec, tok, linep, tree);
		expandise(tok, tree);
		linep += tok->read_size;
	}
	commandise(tree, toks);
	if (mode_flag == FLAG_DEBUG || mode_flag == FLAG_DEBUG_ENVP)
		print_debugging(toks, tree);
	ft_add_history(line, linec, tree);
	return (SUCCESS);
}

static void	tok_init(t_token **tok, t_vec *tokens, t_tree *tree)
{
	t_token	*new;

	new = NULL;
	if (!ft_arena_alloc(tree->a_buf, (void **)&new, sizeof(t_token)))
		exit_parser(tree, MSG_MALLOCF);
	new->tok_chars = NULL;
	if (!vec_alloc(&new->tok_chars, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	new->type = TOK_DEFAULT;
	new->redirect = RDR_DEFAULT;
	new->quote_type = QUO_DEFAULT;
	new->quote_char = '\0';
	new->expand = false;
	new->read_size = 1;
	new->heredoc = NULL;
	*tok = new;
	if (!vec_push(tokens, tok))
		exit_parser(tree, MSG_MALLOCF);
}

static bool	ft_nothingtodo(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		return (true);
	return (false);
}

static int	lexer_init(t_vec **tokens, t_vec **linec, char *line, t_tree *tree)
{
	if (!tokens || !tree)
		exit_parser(tree, MSG_UNINTAL);
	if (!ft_arena_init(&tree->a_buf, ARENA_BUF)
		|| !vec_alloc(tokens, tree->a_buf)
		|| !vec_new(*tokens, 0, sizeof(t_token *))
		|| !vec_alloc(linec, tree->a_buf)
		|| !vec_from(*linec, line, ft_strlen(line), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	return (SUCCESS);
}

static void ft_rl_append(t_vec *linec, t_token *tok, char *line, t_tree *tree)
{
	t_vec	*tmp;
	char	nl;

	if (!tok->heredoc)
		return ;
	(void)line;
	tmp = NULL;
	nl = '\n';
	if (!vec_alloc(&tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_from(tmp, tok->heredoc, ft_strlen(tok->heredoc), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_push(linec, &nl))
		exit_parser(tree, MSG_MALLOCF);
	if (!vec_append(linec, tmp))
		exit_parser(tree, MSG_MALLOCF);
	return ;
}

static void	ft_add_history(char **line, t_vec *linec, t_tree *tree)
{
	// TODO: Add exit_readline function insteadd of exit_parser to free(line)
	if (*line)
		free(*line);
	vec_push(linec, &(char){0});
	*line = ft_strdup((char *)linec->data);
	if (!*line)
		exit_parser(tree, MSG_MALLOCF);
	add_history(*line);
}
