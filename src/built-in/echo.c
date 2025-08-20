/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:40:15 by saan              #+#    #+#             */
/*   Updated: 2025/08/20 18:23:00 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd_node *node)
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
		ft_putstr_fd(node->argv[i], node->out_fd);
		if (node->argv[i + 1])
			write(node->out_fd, " ", 1);
		i++;
	}
	if (flag)
		write(node->out_fd, "\n", 1);
}
