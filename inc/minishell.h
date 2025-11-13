/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:07:57 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 17:28:32 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>

# define MSG_FLAG_PROMPT "minishell: use the flag '-debug' to enable debugging"

extern volatile sig_atomic_t	g_receipt;

typedef enum e_flag
{
	FLAG_DEFAULT,
	FLAG_DEBUG,
}	t_flag;

typedef struct s_cmd
{
	size_t	argc;
	char	**argv;
	char	*input;
	char	*output;
	char	*heredoc;
}	t_cmd;

typedef struct s_tree
{
	t_vec	*cmd_tab;
	t_vec	*envp;
	t_arena	*arena;
}	t_tree;

#endif
