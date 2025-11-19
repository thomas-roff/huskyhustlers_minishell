#include "../../inc/minishell.h"
#include "../../inc/execution.h"

//cd changes the currect working directory and updates the environment variables 
//cd with no arg -> HOME
//cd - -> switches to old working directory
//cd -- -> same as cd goes back to HOME 

//./minishell argv[1] argv[2]
//"HOME=/Users/Alice"
//envp has the list HOME=... PATH=...
//the max linux can store a full path is 4096 bytes
//for error handling, there are some cases where you have to return error code and not exit 

int	envp_count(t_cmd *command, t_tree *tree)
{
	int	i;

	i = 0;
	while (tree->envp && tree->envp[i])
		i++;
	return (i);
}

char	**add_new_envp(t_cmd *command, int size, t_tree *tree)
{
	char	**new_envp;
	int		i;

	new_envp = ft_calloc(size + 1, sizeof * new_envp);
	if (!new_envp)
		return (NULL);
	i = 0;
	while (tree->envp[i] != NULL && i < size)
	{
		new_envp[i] = ft_strdup(tree->envp[i]);
		free_ptr(tree->envp[i]);
		i++;
	}
	free(tree->envp);
	return (new_envp);
}

int	envp_index(t_cmd *command, char *envp_name, t_tree *tree)
{
	int		i;
	char	*temp;

	temp = ft_strjoin(envp_name, "=");
	if (!temp)
		return (-1);
	i = 0;
	while (tree->envp[i] != NULL)
	{
		if (ft_strncmp(temp, tree->envp[i], ft_strlen(temp)) == 0)
		{
			free_ptr(temp);
			return (i);
		}
		i++;
	}
	free_ptr(temp);
	return (-1);
}

int	change_envp(t_cmd *command, char *envp_name, char *new_path, t_tree *tree)
{
	int		index;
	char	*temp;

	if (new_path == NULL)
		new_path = "";
	temp = ft_strjoin("=", new_path);
	if (!temp)
		return (0);
	index = envp_index(command, envp_name, tree); //if envp_name exist
	if (index != -1 && tree->envp[index] != NULL)
	{
		free_ptr(tree->envp[index]);
		tree->envp[index] = ft_strjoin(envp_name, temp);
	}
	else //if envp_name doesnt exist yet
	{
		index = envp_count(command, tree);
		tree->envp = add_new_envp(command, index + 1, tree);
		if (!tree->envp)
			return (0);
		tree->envp[index] = ft_strjoin(envp_name, temp);
	}
	free_ptr(temp);
	return (1);
}

void	update_dir(t_cmd *command, char *cwd, t_tree *tree)
{
	char *temp = NULL;

	temp = find_envp(tree, "PWD");
	if (temp)
		change_envp(tree, "OLDPWD", temp);
	
	change_envp(command, "OLDPWD", find_envp(tree, "PWD"), tree);
	change_envp(command, "PWD", cwd, tree);
	if (command->old_working_dir != NULL)
	{
		free_ptr(command->old_working_dir);
		command->old_working_dir = ft_strdup(command->working_dir);
	}
	if (command->working_dir != NULL)
	{
		free_ptr(command->working_dir);
		command->working_dir = ft_strdup(cwd);
	}
	free_ptr(cwd);
}

int	change_dir(t_cmd *command, char *path, t_tree *tree)
{
	char	*cwd_path;
	char	*temp;
	char	buffer[4096];

	if (chdir(path) != 0) //changed to "/Users/Alice"
		return (print_error("cd", path));
	cwd_path = getcwd(buffer, 4096);
	if (!cwd_path)
	{
		print_error("cd", "error retrieving current directory");
		print_error("getcwd", "cannot access parent directories");
		//FIXME: fallback path so that command->working_dir is never NULL
		cwd_path = ft_strjoin(command->working_dir, "/");
		temp = cwd_path;
		cwd_path = ft_strjoin(temp, path);
		free_ptr(temp);
	}
	else
		cwd_path = ft_strdup(buffer); //allocates to the heap memory
	update_dir(command, cwd_path, tree);
	return (1);
}

char	*find_envp( t_tree *tree, char *path)
{
	int		i;
	char	*temp;
	t_keyval *key_value;

	i = 0;
	while (i < tree->envp->len)
	{
		key_value = *(t_keyval **)vec_get(tree->envp, i);
		if (strcmp(key_value->key, path) == 0)
			return (key_value->value);
		i++;
	}
	return (NULL);
}


int cd_built_in_command (t_cmd *command, t_tree *tree)
{
	char *path;

	//switching to HOME
	if (command->argv == NULL || command->argv[1] == NULL || is_space(command->argv[1][0]) == 1
		|| command->argv[1][0] == '\0' || ft_strncmp(command->argv[1], "--", 3) == 0) 
	{
		path = find_envp(tree, "HOME");
		if (path == NULL || *path == '\0' || is_space(*path) == 1)
		{
			return (print_error("cd", "HOME not set")); //FIXME check if it should exit or return err
		}
		change_dir(command, path, tree);
		return (0);
		
	}
	if (command->argv[2] != NULL)
		return(print_error("cd", "too many arguments"));
	if (ft_strncmp(command->argv[1], "-", 2) == 0)
	{
		path = find_envp(tree, "OLDPWD");
		if (!path)
			return(print_error("cd", "OLDPWD not set"));
		change_dir(command, path, tree);
		return (0);
	}
	change_dir(command, command->argv[1], tree);
	return (0);
}
