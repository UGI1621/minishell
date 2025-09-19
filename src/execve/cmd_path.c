/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:15:39 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 02:48:37 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_cmd_name(char *cmd)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(ft_strrchr(cmd, '/')));
	else
		return (ft_strdup(cmd));
}

static char	*access_absolut_paths(char *cmd, t_cmd_list *list,
		t_env_list *my_env, char **path)
{
	free_2ptr(path);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
		write_access_error(cmd, list, my_env);
	return (NULL);
}

static char	*access_paths(char **paths, char *cmd, t_cmd_list *list,
		t_env_list *my_env)
{
	int		i;
	char	*temp;

	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin_af(ft_strdup(paths[i]), ft_strdup(cmd));
		if (access(temp, X_OK) == 0)
			break ;
		free(temp);
		temp = NULL;
	}
	if (!temp)
	{
		free_2ptr(paths);
		write_cmd_nf(cmd, list, my_env);
	}
	return (temp);
}

void	check_and_set_argv(t_cmd_node *node, t_env_list *my_env,
		t_cmd_list *list)
{
	char	*cmd;
	char	*temp;
	char	**paths;
	DIR		*dir;

	paths = ft_split(get_env("PATH", my_env), ':');
	cmd = ft_strdup(node->argv[0]);
	dir = opendir(cmd);
	if (dir)
	{
		free_2ptr(paths);
		write_is_dir(dir, cmd, list, my_env);
	}
	if (!ft_strchr(cmd, '/'))
	{
		cmd = ft_strjoin_af(ft_strdup("/"), cmd);
		temp = access_paths(paths, cmd, list, my_env);
	}
	else
		temp = access_absolut_paths(cmd, list, my_env, paths);
	free_2ptr(paths);
	free(cmd);
	node->cmd_path = temp;
}
