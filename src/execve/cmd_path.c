/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 15:15:39 by saan              #+#    #+#             */
/*   Updated: 2025/08/17 17:04:02 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*access_paths(char **paths, char *cmd)
{
	int	i;
	int	flag;
	char	*temp;

	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin_af(ft_strdup(paths[i]), ft_strdup(cmd));
		flag = access(temp, X_OK);
		if (flag == 0)
			break ;
		free(temp);
		temp = NULL;
	}
	if (!temp)
		write_access_error(++cmd);
	return (temp);
}

void	check_and_set_argv(t_cmd_node *node)
{
	char	*cmd;
	char	*temp;
	char	**paths;

	if (ft_strchr(node->argv[0], '/'))
		cmd = ft_strdup(node->argv[0]);
	else
		cmd = ft_strjoin_af(ft_strdup("/"), ft_strdup(node->argv[0]));
	paths = ft_split(getenv("PATH"), ':');
	temp = access_paths(paths, cmd);
	free_2ptr(paths);
	free(cmd);
	free(node->argv[0]);
	node->argv[0] = temp;
}
