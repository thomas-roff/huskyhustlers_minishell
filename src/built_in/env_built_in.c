
#include "../../inc/minishell.h"
#include "../../inc/execution.h"

int	env_built_in_command(t_cmd *command)
{
	int	i;

	if (command->argv != NULL && command->argv[1] != NULL)
		return (print_error("envp", "too many arguments"));
	i = 0;
	if (!command->envp)
		return (1);
	while (command->envp[i])
		ft_putendl_fd(command->envp[i++], 1);
	return (0);
}