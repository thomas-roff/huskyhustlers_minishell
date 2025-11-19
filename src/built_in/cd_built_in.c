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

int	envp_index(t_tree *tree, char *envp_key)
{
	int		i;
	t_keyval	*key_value;

	i = 0;

	if (!tree || !tree->envp)
		return (-1);

	while (i < (int)tree->envp->len)
	{
		key_value = *(t_keyval **)vec_get(tree->envp, i);
		if (strcmp(key_value->key, envp_key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	change_envp(t_tree *tree, char *envp_key, char *new_path)
{
	int		index;
	t_keyval *key_value;

	if (new_path == NULL)
		new_path = "";

	index = envp_index(tree, envp_key);

	if (index != -1)
	{
		key_value = *(t_keyval**)vec_get(tree->envp, index);
		free_ptr(key_value->value);
		key_value->value = ft_strdup(new_path);
	}
	else //if envp_key doesnt exist yet
	{
		key_value = malloc(sizeof(t_keyval));
		if (!key_value)
			return (0);
		key_value->key = ft_strdup(envp_key);
		key_value->value = ft_strdup(new_path);

		if (!key_value->key || !key_value->value) //FIXME: Do I need to free the memory?
			return (0);
		vec_push(tree->envp, &key_value);
		return (1);
	}
	return (1);
}

void	update_dir(t_cmd *command, char *cwd, t_tree *tree)
{
	char *temp = NULL;

	temp = find_envp(tree, "PWD");
	if (temp)
		change_envp(tree, "OLDPWD", temp);

	change_envp(tree, "PWD", temp);

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
	t_keyval *key_value;

	i = 0;
	while (i < (int)tree->envp->len)
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
