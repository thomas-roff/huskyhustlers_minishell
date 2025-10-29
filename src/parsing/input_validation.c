/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/10/28 11:31:08 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	input_check(char *args)
{
	if 
	return (OK);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 1)
		return (EXIT_SUCCESS);
	while (i < argc)
		if (input_check(argv[i++]) < 0)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
