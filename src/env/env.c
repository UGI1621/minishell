/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 05:45:38 by saan              #+#    #+#             */
/*   Updated: 2025/08/29 07:17:30 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_cur_cmd(t_env_list *my_env, char **args)
{
	t_env_node	*node;
	char	*temp;
	int		i;

	i = 0;
	while (args[i])
		i++;
	node = my_env->head;
	while(node)
	{
		if (!ft_strncmp(node->key, "_", ft_strlen(node->key)))
			break ;
		node = node->next;
	}
	free(node->val);
	if (i == 0)
		node->val = ft_strdup("");
	else
		node->val = ft_strdup(args[i - 1]);
}

void	env_free(t_env_list *my_env)
{
	t_env_node	*node;
	t_env_node	*temp;

	node = my_env->head;
	while (node)
	{
		if (node->key)
			free(node->key);
		if (node->val)
			free(node->val);
		temp = node;
		node = node->next;
		free(temp);
	}
}

void	check_cmd_env(t_env_list *my_env)
{
	t_env_node *en = my_env->head;
	while (en)
	{
		if (!ft_strncmp(en->key, "_", ft_strlen(en->key)))
			break ;
		en = en->next;
	}
	printf("\n%s=%s\n",en->key, en->val);
}

void	ft_env(t_cmd_node *node, t_env_list *my_env)
{
	t_env_node	*e_node;

	e_node = my_env->head;
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
	update_cur_cmd(my_env, node->argv);
}
