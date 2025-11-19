#include "../../inc/minishell.h"
#include "../../inc/execution.h"

//echo prints text to the standard output 
//splits "Hello World" and joins them back again with space and prints them with \n
//echo -n prints without a newline 


int	with_newline_flag(char *cmd_argv)
{
	int		i;
	int		newline_flag;

	newline_flag = 0;
	i = 0;
	if (cmd_argv[i] != '-')
		return (newline_flag);
	i++;
	while (cmd_argv[i] != '\0' && cmd_argv[i] == 'n') //handling -nnnn
		i++;
	if (cmd_argv[i] == '\0') //checking if everything is n, then is a valid flag
		newline_flag = 1;
	return (newline_flag); //if not return 0 
}

void	echo_print(char **cmd_argv, int newline_flag, int i)
{
	if (cmd_argv[i] == NULL)
	{
		if (newline_flag == 0)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (cmd_argv[i] != NULL)
	{
		ft_putstr_fd(cmd_argv[i], 1);
		if (cmd_argv[i + 1])
			ft_putchar_fd(' ', 1);
		else if (cmd_argv[i + 1] == NULL && newline_flag == 0)
			ft_putchar_fd('\n', 1);
		i++;
	}
}

int	echo_built_in_command(t_cmd *command)
{
	int		i;
	int		newline_flag;

	newline_flag = 0;
	i = 1;
	while (command->argv[i] && with_newline_flag(command->argv[i])) //if newline_flag returns 1
	{
		newline_flag = 1;
		i++;
	}
	echo_print(command->argv, newline_flag, i);
	return (0);
}