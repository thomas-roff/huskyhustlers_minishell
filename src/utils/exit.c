/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 11:45:20 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/20 16:36:39 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	exit_parser(t_tree *tree, char *error)
{
	if (tree)
	{
		if (tree->a_buf)
			ft_arena_list_free(&tree->a_buf);
		if (tree->a_sys)
			ft_arena_list_free(&tree->a_sys);
	}
	if (error)
		ft_perror(error);
	exit(EXIT_FAILURE);
}

int	ft_perror(char *s)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	write(2, "\n", 1);
	return (FAIL);
}
