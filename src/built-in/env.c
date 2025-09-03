/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:45:38 by saan              #+#    #+#             */
/*   Updated: 2025/09/02 06:00:12 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_cmd_node *node, t_env_list *my_env, int save_stdin, int save_stdout)
{
	t_env_node	*e_node;

	e_node = my_env->head;
	if (node->argv[1])
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	while(e_node)
	{
		if (e_node->val)
		{
			ft_putstr_fd(e_node->key, STDOUT_FILENO);
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putendl_fd(e_node->val, STDOUT_FILENO);
		}
		e_node = e_node->next;
	}
	set_iofds(save_stdin, save_stdout);
	return (0);
}
