#include "../../inc/minishell.h"
#include "../../inc/execution.h"


//TODO: Built-in commmands for exit 
int execute_built_in(t_cmd *command, t_tree *tree)
{
	int result;

	result = 0;

	if (ft_strncmp(command->argv[0], "cd", 3) == 0)
		result = cd_built_in_command(command, tree);
	else if (ft_strncmp(command->argv[0], "env", 4) == 0) 
	 	result = env_built_in_command(command);
	else if (ft_strncmp(command->argv[0], "pwd", 4) == 0) 
		result = pwd_built_in_command(command);
	else if (ft_strncmp(command->argv[0], "unset", 7) == 0) 
		result = unset_built_in_command(command);
	else if (ft_strncmp(command->argv[0], "echo",5) == 0) 
		result = echo_built_in_command(command);
	else if (ft_strncmp(command->argv[0], "export", 8) == 0) 
		result = export_built_in_command(command);
	else
		printf("error in execute_built_in function\n");

	return (result);
}

// int initialize_dir(t_cmd *command)
// {
// 	char buffer[4096];
// 	char *working_dir;

// 	working_dir = getcwd(buffer, 4096);
// 	command->working_dir = ft_strdup(working_dir);
// 	if (!command->working_dir)
// 		return (0);
// 	return (1);
// }

// void	executor(t_tree *tree, t_flag mode_flag)
// {
// 	t_vec	*user_prompt;
// 	t_cmd	*command;
// 	size_t	i;
// 	size_t	j;

// 	// Casting pointer, but you could just work with tree->cmd_tab
// 	user_prompt = tree->cmd_tab;
// 	i = 0;
// 	while (i < user_prompt->len) //looping the CMD[0], CMD[1], etc  
// 	{	
// 		command = *(t_cmd **)vec_get(user_prompt, i);
// 		i++;
// 	}
// 	//Check if there is pipe or not 


// 	execute_built_in(command); 


// 	(void)mode_flag;
// }

// static int	get_children(t_cmd *command)
// {
// 	pid_t	wpid;
// 	int		status;
// 	int		save_status;

// 	close_fds(command->cmd, false);
// 	save_status = 0;
// 	wpid = 0;
// 	while (wpid != -1 || errno != ECHILD)
// 	{
// 		wpid = waitpid(-1, &status, 0);
// 		if (wpid == command->pid)
// 			save_status = status;
// 		continue ;
// 	}
// 	if (WIFSIGNALED(save_status))
// 		status = 128 + WTERMSIG(save_status);
// 	else if (WIFEXITED(save_status))
// 		status = WEXITSTATUS(save_status);
// 	else
// 		status = save_status;
// 	return (status);
// }


// static int	create_children(t_cmd *command)
// {
// 	t_command	*cmd;

// 	cmd = command->cmd;
// 	while (command->pid != 0 && cmd)
// 	{
// 		command->pid = fork();
// 		if (command->pid == -1)
// 			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
// 		else if (command->pid == 0)
// 			execute_command(command, cmd);
// 		cmd = cmd->next;
// 	}
// 	return (get_children(command));
// }

/* restore_io:
*	Restores the original standard input and standard output
*	to their original fds of 0 and 1. Used to clear the input/output
*	fds after execution, in preparation for the next set of user commands.
*	Returns 1 if the duplication was successful, 0 if not.
*/
// bool	restore_io(t_io_fds *io)
// {
// 	int	ret;

// 	ret = true;
// 	if (!io)
// 		return (ret);
// 	if (io->stdin_backup != -1)
// 	{
// 		if (dup2(io->stdin_backup, STDIN_FILENO) == -1)
// 			ret = false;
// 		close(io->stdin_backup);
// 		io->stdin_backup = -1;
// 	}
// 	if (io->stdout_backup != -1)
// 	{
// 		if (dup2(io->stdout_backup, STDOUT_FILENO) == -1)
// 			ret = false;
// 		close(io->stdout_backup);
// 		io->stdout_backup = -1;
// 	}
// 	return (ret);
// }

// /* redirect_io:
// *	Duplicates the input and output fds to the standard input and output.
// *	Backs up the standard input and output before replacing them in order
// *	to restore them after execution.
// *	Returns 1 for success, 0 in case of error.
// */
// bool	redirect_io(t_io_fds *io)
// {
// 	int	ret;

// 	ret = true;
// 	if (!io)
// 		return (ret);
// 	io->stdin_backup = dup(STDIN_FILENO);
// 	if (io->stdin_backup == -1)
// 		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
// 	io->stdout_backup = dup(STDOUT_FILENO);
// 	if (io->stdout_backup == -1)
// 		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
// 	if (io->fd_in != -1)
// 		if (dup2(io->fd_in, STDIN_FILENO) == -1)
// 			ret = errmsg_cmd("dup2", io->infile, strerror(errno), false);
// 	if (io->fd_out != -1)
// 		if (dup2(io->fd_out, STDOUT_FILENO) == -1)
// 			ret = errmsg_cmd("dup2", io->outfile, strerror(errno), false);
// 	return (ret);
// }

// /* check_infile_outfile:
// *	Checks if the infile and outfile are set correctly.
// *	Returns 1 on success, 0 on failure.
// */
// bool	check_infile_outfile(t_io_fds *io)
// {
// 	if (!io || (!io->infile && !io->outfile))
// 		return (true);
// 	if ((io->infile && io->fd_in == -1)
// 		|| (io->outfile && io->fd_out == -1))
// 		return (false);
// 	return (true);
// }

/* close_pipe_fds:
*	Closes the pipe fds of all commands. A pointer to a command to skip
*	can be specified to skip closing that command's pipe fds:
*		- The parent will specify NULL for the skip command while closing
*		all pipe fds.
*		- The child will specify its own command as skip command while
*		closing all pipe fds so as to not accidentally close its own
*		pipe fds.
*/
// void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
// {
// 	while (cmds)
// 	{
// 		if (cmds != skip_cmd && cmds->pipe_fd)
// 		{
// 			close(cmds->pipe_fd[0]);
// 			close(cmds->pipe_fd[1]);
// 		}
// 		cmds = cmds->next;
// 	}
// }

// /* create_pipes:
// *	Creates a set of pipes for each piped command in the list
// *	of commands.
// *	Returns 1 if successful, 0 in case of failure.
// */
// bool	create_pipes(t_data *data)
// {
// 	int			*fd;
// 	t_command	*tmp;

// 	tmp = data->cmd;
// 	while (tmp)
// 	{
// 		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
// 		{
// 			fd = malloc(sizeof * fd * 2);
// 			if (!fd || pipe(fd) != 0)
// 			{
// 				free_data(data, false);
// 				return (false);
// 			}
// 			tmp->pipe_fd = fd;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (true);
// }

// /* set_pipe_fds:
// *	Sets the pipe fds for this command. If the previous command
// *	was piped to this one, sets the input as the read end of
// *	the previous command. If this command is piped to the
// *	next, sets the output ad the write end of the pipe.
// *		pipe_fd[0] = read end of pipe.
// *		pipe_fd[1] = write end of pipe.
// *	Returns true when the pipe file descriptors are set.
// */
// bool	set_pipe_fds(t_command *cmds, t_command *c)
// {
// 	if (!c)
// 		return (false);
// 	if (c->prev && c->prev->pipe_output)
// 		dup2(c->prev->pipe_fd[0], STDIN_FILENO);
// 	if (c->pipe_output)
// 		dup2(c->pipe_fd[1], STDOUT_FILENO);
// 	close_pipe_fds(cmds, c);
// 	return (true);
// }



// int	check_infile_outfile(t_cmd *command)
// {
// 	//init io FIXME: needs to be done in the beginning 
// 	command->fd_infile == -1;
// 	command->fd_outfile == -1;


// 	if (!command || (!command->input && !command->output))
// 		return (1);
// 	if ((command->input && command->fd_infile == -1) //CHECK AGAIN 
// 		|| (command->output && command->fd_outfile == -1))
// 		return (0);
// 	return (1);
// }

// int	prep_for_exec(t_cmd *command)
// {
// 	if (command == NULL)
// 		return (0);
// 	if (!check_infile_outfile(command))
// 		return (1);
// 	if (!create_pipes(command))
// 		return (0);
// 	return (127);
// }

int	executor(t_tree *tree, t_flag mode_flag)
{
	int	result;
	t_vec	*cmds;
	t_cmd	*cmd;

	result = 0;

	cmds = tree->cmd_tab;
	if (cmds->len == 0)
		return (0); //FIXME: check whether it should be exit or return with error code

	cmd = *(t_cmd **)vec_get(cmds, 0);

	//prepare for command command.
	//1. Handle null or empty commands
	//2. Handle redirection only commands
	//3. Verify redirection files 
	//4. Set up pipes for pipeline commands 
	//5. Tell the executor what to do next via return codes


	// result = prep_for_exec(cmd);
	// if (result != 127)
	// 	return (result);
	
	//only for one built-in commands - no fork. TODO: 
	//1. Check that pipe_output is not equal to 1 
	//2. Check all redirection files or heredocs are valid and can be opened 
	if (cmds->len == 1) 
	{
		result = execute_built_in(cmd, tree);
	}
	//return (create_children(cmd));
	(void)mode_flag;
	return (result);
}

