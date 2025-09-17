/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 05:51:40 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 18:01:51 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_env(char *key, t_env_list *my_env)
{
	t_env_node	*node;

	node = my_env->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			if (node->prev)
				node->prev->next = node->next;
			else
				my_env->head = node->next;
			if (node->next)
				node->next->prev = node->prev;
			free(node->key);
			free(node->val);
			free(node);
			break ;
		}
		node = node->next;
	}
}

char	*get_env(char *key, t_env_list *my_env)
{
	t_env_node	*node;

	node = my_env->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node->val);
		node = node->next;
	}
	return (NULL);
}

void	set_env(char *key, char *val, int *set_flag, t_env_list *my_env)
{
	t_env_node	*node;

	node = my_env->head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			if (!(*set_flag))
				return ;
			free(node->val);
			node->val = ft_strdup(val);
			return ;
		}
		node = node->next;
	}
	node = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	node->prev = NULL;
	node->key = ft_strdup(key);
	node->val = ft_strdup(val);
	node->next = NULL;
	add_env_node(my_env, node);
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
	free(my_env);
}
