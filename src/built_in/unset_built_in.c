
#include "../../inc/minishell.h"
#include "../../inc/execution.h"

//Rules for envp_name:
//only accept envp_name that starts with letters, reject any that starts with digit 
//or invslid characters "-" "?" "/" etc
//digit can exist in the name "PATH2" but cannot start with digit "2PATH"(REJECT)
//cannot contain "="

int	remove_envp(t_cmd *command, int index)
{
	int	i;

	if ( index < 0 || index > envp_count(command))
		return (0);
	free_ptr(command->envp[index]); //removes it
	i = index;
	while (command->envp[i + 1] != NULL) //move everything up by 1 
	{
		command->envp[i] = command->envp[i + 1];
		i++;
	}
	command->envp[i] = NULL;
	return (1);
}


int	is_valid_envp(char *envp_name)
{
	int	i;

	i = 0;
	if (ft_isalpha(envp_name[i]) == 0 && envp_name[i] != '_')
		return (0);
	i++;
	while (envp_name[i] && envp_name[i] != '=')
	{
		if (ft_isalnum(envp_name[i]) == 0 && envp_name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}


int	unset_built_in_command(t_cmd *command)
{
	int	i;
	int	index;
	int	result;

	result = 0;
	i = 1;
	while (command->argv[i] != NULL)
	{
		if (is_valid_envp(command->argv[i]) == 0 || ft_strchr(command->argv[i], '=') != NULL) //make sure the envp_var does not contain '='
		{
			print_error("unset", "not a valid identifier");
			result = 1;
		}
		else
		{
			index = envp_index(command, command->argv[i]);
			if (index != -1) //FIXME: not sure what it should return when index == -1
				remove_envp(command, index);
		}
		i++;
	}
	return (result);
}