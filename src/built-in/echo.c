/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:40:15 by saan              #+#    #+#             */
/*   Updated: 2025/09/02 05:58:51 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd_node *node, t_env_list *my_env, int save_stdin, int save_stdout)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	if (node->argv[i] && !ft_strncmp(node->argv[i], "-n", ft_strlen(node->argv[i])))
	{
		flag = 0;
		i++;
	}
	while (node->argv[i])
	{
		ft_putstr_fd(node->argv[i], STDOUT_FILENO);
		if (node->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	set_iofds(save_stdin, save_stdout);
	return (0);
}
