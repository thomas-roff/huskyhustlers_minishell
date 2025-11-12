/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:17:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/12 18:11:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

void	print_tokens(t_vec *tokens)
{
	t_token	*tok;
	size_t	i;

	i = 0;
	while (i < tokens->len)
	{
		tok = *(t_token **)vec_get(tokens, i);
		vec_printf_s(tok->tok_chars);
		i++;
	}
}

void	print_cmd_tab(t_vec *cmd_tab)
{
	t_cmd	*cmd;
	size_t	i;
	size_t	j;

	i = 0;
	ft_printf("COMMAND TABLE\n");
	while (i < cmd_tab->len)
	{
		j = 0;
		cmd = *(t_cmd **)vec_get(cmd_tab, i);
		ft_printf("CMD %u\n", (uint32_t)i + 1);
		ft_printf("argc: %u\n", (uint32_t)cmd->argc);
		while (j < cmd->argc)
		{
			ft_printf("argv[%u]: %s ", (uint32_t)j, cmd->argv[j]);
			j++;
		}
		ft_printf("\ninput: %s ouput: %s\n", cmd->input, cmd->output);
		i++;
	}
}
