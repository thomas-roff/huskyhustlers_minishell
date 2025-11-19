#include "../../inc/execution.h"
#include "../../inc/minishell.h"

int is_space(char c)
{
	if (c <= 32)
		return (1);
	else 
		return (0);
}

// void	clean_exit(int *pipe_fd, char *msg, int exit_code)
// {
// 	errno = exit_code;
// 	if (errno == 127)
// 	{
// 		ft_putstr_fd("pipex: ", 2);
// 		ft_putstr_fd(msg, 2);
// 		ft_putstr_fd(" command not found\n", 2);
// 	}
// 	else
// 		perror(msg);
// 	if (pipe_fd)
// 	{
// 		close(pipe_fd[0]);
// 		close(pipe_fd[1]);
// 	}
// 	exit(exit_code);
// }

//print error message (minishell: cd: projects: No such file or directory)
int print_error(char *cmd, char *msg)
{
	if (errno == ESTALE) //handle stale files 
		errno = ENOENT;
	ft_putstr_fd("minishell: ", 2);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg != NULL)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(strerror(errno), 2);
	return (1);
}

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}