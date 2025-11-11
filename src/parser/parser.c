/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:41:21 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:23:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	token_reset(t_token *token);

static void	init_lexer(t_vec **tokens, t_tree *tree);
static bool	ft_nothingtodo(char **line);

int	parser(t_tree *tree, char *line)
{
	t_vec	*tokens;
	size_t	i;
	// t_token	*token;

	if (!tree || !line)
		return (FAIL);
	if (!valid_input(line))
		return (FAIL);
	if (ft_nothingtodo(&line))
		return (SUCCESS);
	init_lexer(&tokens, tree);
	i = 0;
	// while (*line)
	// {
	// 	tokenise(vec_get(&tokens, i), line, tree);
	// 	if (token->expand == true)
	// 		expandise(token, tree);
	// 	vec_printf_s(token->tok_chars);
	// 	line += token->read_size;
	// 	i++;
	// }
	// commandise(tree, token);
	return (SUCCESS);
}

static bool	ft_nothingtodo(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if (!**line)
		return (true);
	return (false);
}

static void	init_lexer(t_vec **tokens, t_tree *tree)
{
	t_vec	*new;

	if (!tokens || !tree)
		clean_exit(tree, MSG_UNINTAL);
	if (!ft_arena_init(&tree->arena, ARENA_BUF))
		clean_exit(tree, MSG_MALLOCF);
	// ft_printf("I got here\n");
	// vec_init(tokens, 1, sizeof(t_token), tree->arena);
	// vec_putvars(tokens);
	if (!vec_new(tokens, 1, sizeof(t_token)))
		clean_exit(tree, MSG_MALLOCF);
	if (!ft_arena_alloc(tree->arena, (void **)token, sizeof(t_token)))
		clean_exit(tree, "malloc fail 3");
	new = *token;
	new->tok_chars = NULL;
	if (!vec_alloc(&new->tok_chars, tree->arena))
		clean_exit(tree, "malloc fail 4");
	new->type = TOK_DEFAULT;
	new->redirect = RDR_DEFAULT;
	new->quote = '\0';
	new->expand = false;
	new->read_size = 1;
}
