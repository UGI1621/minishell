/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:06:40 by saan              #+#    #+#             */
/*   Updated: 2025/08/28 15:19:19 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_cmd_node *node)
{
	char	*cur_path;

	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		perror("minishell: getcwd");
		g_sigs.exit_code = errno;
	}
	ft_putendl_fd(cur_path, STDOUT_FILENO);
	free(cur_path);
}
