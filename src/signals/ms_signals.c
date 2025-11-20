/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/20 17:06:52 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/signals.h"
// #include "../../inc/minishell.h"

static void	handle_sig(int sig)
{
	if (sig == 2)
	{
		g_receipt = EXIT_CTRLC;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 3)
	{
		g_receipt = EXIT_CTRLQ;
		// TODO: What happens when CTRL \ is called?
	}
}

void	init_ms_signals(int	action)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	if (action == TURN_ON)
	{
		sa.sa_handler = &handle_sig;
		sa.sa_flags = SA_RESTART;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = SA_RESTART;
	}
}
