/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:59:02 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/15 11:12:16 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parsing.h"

static size_t	expand_parse(t_token *tok, t_vec *tmp, size_t i, t_tree *tree);
static size_t	expand_len(size_t *start, t_token *tok, size_t i);
static int		expand_env_var(t_vec *tmp, t_tree *tree);
static void		expand_rm(t_token *tok, size_t *start, size_t len);

void	expandise(t_token *tok, t_tree *tree)
{
	t_vec	*tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (!vec_alloc(&tmp, tree->a_buf))
		exit_parser(tree, MSG_MALLOCF);
	while (i < tok->tok_chars->len)
	{
		if (((char *)tok->tok_chars->data)[i] == '$')
		{
			i += expand_parse(tok, tmp, i, tree);
			if (tmp->len > 0)
				vec_reset(tmp);
		}
		else
			i++;
	}
}

static size_t	expand_parse(t_token *tok, t_vec *tmp, size_t i, t_tree *tree)
{
	size_t	start;
	size_t	len;

	start = 0;
	len = expand_len(&start, tok, i);
	if (len == 0)
	{
		expand_rm(tok, &start, len);
		return (0);
	}
	if (!vec_from(tmp, vec_get(tok->tok_chars, start), len + 1, sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	tmp->data[len] = '\0';
	expand_rm(tok, &start, len);
	if (!expand_env_var(tmp, tree))
		return (0);
	if (!vec_inpend(tok->tok_chars, tmp, start))
		exit_parser(tree, MSG_MALLOCF);
	return (tmp->len);
}

static size_t	expand_len(size_t *start, t_token *tok, size_t i)
{
	char	*str;
	size_t	str_len;
	size_t	len;

	i++;
	str = (char *)tok->tok_chars->data;
	str_len = tok->tok_chars->len;
	len = 0;
	while (i + len < str_len
		&& str[i + len] != '$'
		&& str[i + len] != ' ')
		len++;
	*start = i;
	return (len);
}

static int	expand_env_var(t_vec *tmp, t_tree *tree)
{
	const char	*env_var;

	env_var = getenv((char *)tmp->data);
	if (!env_var)
		return (FAIL);
	vec_reset(tmp);
	if (!vec_from(tmp, (void *)env_var, ft_strlen(env_var), sizeof(char)))
		exit_parser(tree, MSG_MALLOCF);
	vec_pop(NULL, tmp);
	return (SUCCESS);
}

static void	expand_rm(t_token *tok, size_t *start, size_t len)
{
	*start -= 1;
	len += 1;
	vec_trim(tok->tok_chars, *start, len);
}
