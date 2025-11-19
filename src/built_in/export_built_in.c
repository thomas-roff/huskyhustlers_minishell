#include "../../inc/minishell.h"
#include "../../inc/execution.h"


//TODO: export a="   "

char	**get_key_value(char *argv)
{
	char	**tmp;
	char	*equal_sign;

	equal_sign = ft_strchr(argv, '=');
	tmp = malloc((sizeof *tmp) * 3);
	tmp[0] = ft_substr(argv, 0, equal_sign - argv);
	tmp[1] = ft_substr(equal_sign, 1, ft_strlen(equal_sign));
	tmp[2] = NULL;
	return (tmp);
}

int	export_built_in_command(t_cmd *command)
{
	int		i;
	char	**tmp;
	int		result;

	result = 0;
	i = 1;
	if (!command->argv[i])
		return (env_built_in_command(command));
	while (command->argv[i])
	{
		if (!is_valid_envp(command->argv[i]))
		{
			print_error("export", "not a valid identifier");
			result = 1;
		}
		else if (ft_strchr(command->argv[i], '=') != NULL)
		{
			tmp = get_key_value(command->argv[i]);
			change_envp(command, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return (result);
}