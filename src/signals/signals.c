/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:46:24 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 17:50:35 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/signals.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_printf("Signal received\n");
}

void	handle_sigquit(int sig)
{
	(void)sig;
	ft_printf("Signal received\n");
}

void	init_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
