/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:06:40 by saan              #+#    #+#             */
/*   Updated: 2025/09/10 01:37:17 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_cmd_node *node, int save_stdin, int save_stdout)
{
	char	*cur_path;

	if (node->argv[1])
	{
		ft_putendl_fd("minishell: pwd: too many arguments", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		perror("minishell: getcwd");
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	ft_putendl_fd(cur_path, STDOUT_FILENO);
	free(cur_path);
	set_iofds(save_stdin, save_stdout);
	return (0);
}
