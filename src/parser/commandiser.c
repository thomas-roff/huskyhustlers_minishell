/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 12:03:45 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:22:48 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

// TODO: Implement copy functions to transfer tokens to tree one by one

void	commandise(t_tree *tree, t_token *token)
{
	(void)tree;
	(void)token;
	// if (!tree->cmd_tab)
	// 	init_cmd_table(tree);
	// if (!tree || !token)
	// 	return ;
	// if (token->type == TOK_WORD || token->type == TOK_QUOTATION)
	// 	parse_word(tree, token);
	// if (token->type == TOK_REDIRECT)
	// 	parse_redirect(tree, token);
}
