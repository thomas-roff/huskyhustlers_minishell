/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 17:58:39 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/04 15:51:24 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parsing.h"

void	signal_handler(int sig)
{
	ft_printf("Signal received\n");
}

// int	main(int argc, char **argv)
// {
// 	struct sigaction	sa;
//
// 	sa.sa_handler = &signal_handler;
// 	return (EXIT_SUCCESS);
// }

int	main(void)
{
	t_tree	*tree;
	t_cmd	*cmd1;
	char	*echo = "echo";
	char	*arg1 = "hi";
	char	*arg2 = "hi";
	char	*command;
	char	*argument1;
	char	*argument2;

	if (!vec_from(tree->cmd_tab, (void *)cmd1, 1, sizeof(t_cmd)))
		return (ft_perror(MSG_MALLOCF));
	if (!vec_from(cmd1->cmd, (void *)echo, 1, sizeof(char *)))
		return (ft_perror(MSG_MALLOCF));
	if (!vec_from(cmd1->args, (void *)arg1, 1, sizeof(char *)))
		return (ft_perror(MSG_MALLOCF));
	if (!vec_push(cmd1->args, arg2))
		return (ft_perror(MSG_MALLOCF));
	command = vec_get(cmd1->cmd, 0);
	argument1 = vec_get(cmd1->cmd, 0);
	argument2 = vec_get(cmd1->cmd, 1);
}
