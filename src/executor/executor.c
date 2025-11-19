#include "../../inc/minishell.h"
#include "../../inc/execution.h"


//TODO: Built-in commmands for exit 
int execute_built_in(t_cmd *command, t_tree *tree)
{
	int result;

	result = 0;

	if (ft_strncmp(command->argv[0], "cd", 3) == 0)
		result = cd_built_in_command(command, tree);
	// else if (ft_strncmp(command->argv[0], "env", 4) == 0) 
	//  	result = env_built_in_command(command);
	else if (ft_strncmp(command->argv[0], "pwd", 4) == 0) 
		result = pwd_built_in_command(command);
	// else if (ft_strncmp(command->argv[0], "unset", 7) == 0) 
	// 	result = unset_built_in_command(command);
	else if (ft_strncmp(command->argv[0], "echo",5) == 0) 
		result = echo_built_in_command(command);
	// else if (ft_strncmp(command->argv[0], "export", 8) == 0) 
	// 	result = export_built_in_command(command);
	else
		printf("error in execute_built_in function\n");

	return (result);
}


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

