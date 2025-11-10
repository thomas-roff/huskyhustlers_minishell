/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:46:33 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/10 12:22:14 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

int	valid_input(char *line)
{
	size_t	len;
	size_t	i;
	char	quote;

	len = ft_strlen(line);
	i = 0;
	quote = '\0';
	if (ft_strnstr(line, ">>>", len))
		return (ft_perror(MSG_SYX_GRE));
	if (ft_strnstr(line, "<<<", len))
		return (ft_perror(MSG_SYX_LES));
	while (i < len)
	{
		ft_isquote(&quote, line[i]);
		if (line[i] == '$' && line[i + 1] == '{'
			&& ft_isbadsubstitute(line + i + 2))
			return (ft_perror(MSG_BAD_SUB));
		if (line[i] == '|' && ft_isdblpipe(line + i))
			return (ft_perror(MSG_SYX_PIP));
		i++;
	}
	if (quote != '\0')
		return (ft_perror(MSG_OPENQUO));
	return (SUCCESS);
}

bool	ft_isbadsubstitute(char *line)
{
	if (ft_isdigit(*line))
		return (true);
	while (*line)
	{
		if (*line == '}')
			return (false);
		if (!ft_isalnum(*line) && *line != '_')
			return (true);
		line++;
	}
	return (false);
}

bool	ft_isquote(char *quote, int c)
{
	if ((c != '"' && c != '\'') || !quote)
		return (false);
	if (c == '"')
	{
		if (*quote == '\0')
			*quote = '"';
		else if (*quote == '"')
			*quote = '\0';
	}
	if (c == '\'')
	{
		if (*quote == '\0')
			*quote = '\'';
		else if (*quote == '\'')
			*quote = '\0';
	}
	return (true);
}

bool	ft_isdblpipe(char *line)
{
	size_t	i;

	i = 1;
	if (line[i] == '|')
		return (false);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '|')
		return (true);
	return (false);
}
