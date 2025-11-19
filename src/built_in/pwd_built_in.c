
#include "../../inc/minishell.h"
#include "../../inc/execution.h"

int	pwd_built_in_command(t_cmd *command)
{
	char	buffer[4096];
	char	*cwd;

	if (command->working_dir != NULL)
	{
		ft_putendl_fd(command->working_dir, 1);
		return (0);
	}
	cwd = getcwd(buffer, 4096);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	print_error("pwd", "Cannot get the current working directory");
	return (1);
}