/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:41:54 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 12:22:53 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_p(t_cmd_list *list, int save_stdin, int save_stdout, t_env_list *my_env)
{
	int	i;
	t_cmd_node *node;

	node = list->head;
	i = 0;
	while (node->argv[i])
		i++;
	if (i >= 3)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	if (i == 2)
	{
		set_iofds(save_stdin, save_stdout);
		i = ft_atoi(node->argv[1]);
		free_cmd_list(list);
		env_free(my_env);
		exit(i);
	}
	return (0);
}

int	ft_exit(t_cmd_node *node, int save_stdin, int save_stdout)
{
	int	i;

	i = 0;
	while (node->argv[i])
		i++;
	if (i >= 3)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	if (i == 2)
	{
		set_iofds(save_stdin, save_stdout);
		exit(ft_atoi(node->argv[1]));
	}
	return (0);
}
