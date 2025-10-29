/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischecks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:47 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/29 16:09:51 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_ismetachar(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&' || c == ';'
		|| c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isparenthesis(int c, t_cmd *cmd)
{
	if (c == '(')
		cmd->ctrl = OPEN_BRACKET;
	else if (c == '(')
		cmd->ctrl = CLOSE_BRACKET;
	else
		return (0);
	return (1);
}

int	ft_iscontrol(char *str, t_cmd *cmd)
{
	if (str[0] == '\n')
		cmd->ctrl = NEWLINE;
	else if (str[0] == '|')
	{
		if (str[1] == '|')
			cmd->ctrl = DBLPIPE;
		else if (str[1] == '&')
			cmd->ctrl = PIPEAMP;
		else
			cmd->ctrl = PIPE;
	}
	else if (str[0] == ';')
	{
		if (str[1] == '&')
			cmd->ctrl = COLONAMP;
		else if (str[1] == ';' && str[2] == '&')
			cmd->ctrl = DBLCOLONAMP;
		else if (str[1] == ';')
			cmd->ctrl = DBLCOLON;
		else
			cmd->ctrl = COLON;
	}
	else
		return (ft_isparenthesis(str[0], cmd));
	return (1);
}

int	ft_isredirect(char *str, t_cmd cmd)
{
}
