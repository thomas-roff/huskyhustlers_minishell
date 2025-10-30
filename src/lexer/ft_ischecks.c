/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischecks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:56:47 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/30 18:57:57 by thblack-         ###   ########.fr       */
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

int	ft_isparenthesis(int c, t_token *token)
{
	if (c == '(')
		token->ctrl = OPEN;
	else if (c == '(')
		token->ctrl = CLOSE;
	else
		return (0);
	return (1);
}

int	ft_iscontrol(char *str, t_token *token)
{
	if (str[0] == '\n')
		token->ctrl = NEWLINE;
	else if (str[0] == '|')
	{
		if (str[1] == '|')
			token->ctrl = DBLPIPE;
		else if (str[1] == '&')
			token->ctrl = PIPEAMP;
		else
			token->ctrl = PIPE;
	}
	else if (str[0] == ';')
	{
		if (str[1] == '&')
			token->ctrl = COLONAMP;
		else if (str[1] == ';' && str[2] == '&')
			token->ctrl = DBLCOLONAMP;
		else if (str[1] == ';')
			token->ctrl = DBLCOLON;
		else
			token->ctrl = COLON;
	}
	else
		return (ft_isparenthesis(str[0], token));
	return (1);
}

int ft_isbracket(int c, t_token *token)
{
	if (c == '\\' || c == '"' || c == '\'')
	{
		if (c == '(')
			token->ctrl = OPEN;
		if (c == '(')
			token->ctrl = CLOSE;
		token->type = TOK_QUOT;
		token->wrap_i++;
		return (1);
	}
	return (0);
}

int	ft_isredirect(char *str, t_token token)
{
	return (1);
}
