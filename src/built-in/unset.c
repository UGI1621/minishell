/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 05:33:28 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 12:42:33 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_env_val(char *key, t_env_list *my_env)
{
	t_env_node	*node;

	node = my_env->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (1);
		node = node->next;
	}
	return (0);
}

int	ft_unset(t_cmd_node *node, int save_stdin, int save_stdout,
		t_env_list *my_env)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	while (node->argv[i])
	{
		if (is_invalid_env_naming_rule(node->argv[i]))
			print_invalid_export(node->argv[i], &flag);
		if (is_env_val(node->argv[i], my_env))
			del_env(node->argv[i], my_env);
		i++;
	}
	set_iofds(save_stdin, save_stdout);
	return (flag);
}
