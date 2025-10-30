/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/30 19:20:07 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	init_lexer(t_tree *tree)
{
	vec_new(&tree->wrap_i, 2, sizeof(char));
}

int	ft_isquote(int c, t_tree *tree)
{
	char	tmp;

	if ((c != '"' && c != '\'') || !tree)
		return (0);
	if (tree->wrap_i.len > 0)
		tmp = *(char *)vec_get(&tree->wrap_i, tree->wrap_i.len - 1);
	else
		tmp = '\0';
	ft_printf("tmp is %c\n", tmp);
	if (c == '"' || c == '\'')
	{
		if (c == '"')
		{
			if (tmp == '"')
				vec_pop(NULL, &tree->wrap_i);
			else
				vec_push(&tree->wrap_i, &c);
		}
		if (c == '\'')
		{
			if (tmp == '\'')
				vec_pop(NULL, &tree->wrap_i);
			else
				vec_push(&tree->wrap_i, &c);
		}
		vec_printf(&tree->wrap_i, 'c');
		return (1);
	}
	return (0);
}

int	lexer(t_tree *tree, char *line)
{
	size_t	i;

	i = 0;
	init_lexer(tree);
	while (line[i])
	{
		ft_isquote(line[i], tree);
		i++;
	}
	return (OK);
}

int	parser(t_tree *tree)
{
	(void)tree;
	return (OK);
}

int	error_msg(t_tree tree)
{
	(void)tree;
	return (OK);
}

int	main(void)
{
	static char	*line;
	t_tree		tree;

	line = NULL;
	while (1)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		line = readline("cmd> ");
		add_history(line);
		vec_from(&tree.line, line, ft_strlen(line), sizeof(char));
		// vec_printf(&tree.line, 's');
		if (!lexer(&tree, line))
			return (error_msg(tree));
		if (!parser(&tree))
			return (error_msg(tree));
		vec_free(&tree.line);
	}
	return (EXIT_SUCCESS);
}
