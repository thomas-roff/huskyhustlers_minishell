/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thblack- <thblack-@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:25:14 by thblack-          #+#    #+#             */
/*   Updated: 2025/11/13 17:37:04 by thblack-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "../libft/inc/libft.h"

# include <errno.h>
# include <string.h>

//EXECUTOR
int	executor(t_tree *tree, t_flag mode_flag);
int execute_built_in(t_cmd *command, t_tree *tree);

//ECHO BUILT IN 
int	echo_built_in_command(t_cmd *command);
void	echo_print(char **cmd_argv, int newline_flag, int i);
int	with_newline_flag(char *cmd_argv);

//CD BUILT IN
int cd_built_in_command (t_cmd *command, t_tree *tree);
char	*find_envp(t_cmd *command, char *path, t_tree *tree);
int	change_dir(t_cmd *command, char *path, t_tree *tree);
void	update_dir(t_cmd *command, char *cwd, t_tree *tree);
int	change_envp(t_cmd *command, char *envp_name, char *new_path, t_tree *tree);
int	envp_index(t_cmd *command, char *envp_name, t_tree *tree);
char	**add_new_envp(t_cmd *command, int size, t_tree *tree);
int	envp_count(t_cmd *command, t_tree *tree);

//ENV BUILT IN
int	env_built_in_command(t_cmd *command);

//EXPORT BUILT IN
int	export_built_in_command(t_cmd *command);
char	**get_key_value(char *argv);

//PWD BUILT IN
int	pwd_built_in_command(t_cmd *command);

//UNSET BUILT IN
int	unset_built_in_command(t_cmd *command);
int	is_valid_envp(char *envp_name);
int	remove_envp(t_cmd *command, int index);

//UTILS
void	free_str_tab(char **tab);
void	free_ptr(void *ptr);
int print_error(char *cmd, char *msg);
int is_space(char c);

#endif
