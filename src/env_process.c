/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:20:02 by saan              #+#    #+#             */
/*   Updated: 2025/08/28 17:22:35 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_list(t_env_list **my_env)
{
	*my_env = (t_env_list *)ft_calloc(1, sizeof(t_env_list));
	(*my_env)->head = NULL;
	(*my_env)->tail = NULL;
}

static void	init_env_node(t_env_node *node, char *env)
{
	int	i;

	i = -1;
	node->prev = NULL;
	while(env[++i])
	{
		if (env[i] == '=')
		{
			node->key = ft_substr(env, 0, i);
			break ;
		}
	}
	node->val = ft_substr(env, i + 1, ft_strlen(env));
	node->next = NULL;
}

static void	add_env_node(t_env_list *list, t_env_node *node)
{
	if(!list->head && !list->tail)
	{
		list->head = node;
		list->tail = node;
	}
	else if (!list->tail->next)
	{
		list->tail->next = node;
		node->prev = list->tail;
		list->tail = node;
	}
}

void	print_env_list(t_env_list *list)
{
	t_env_node *node = list->head;

	while (node)
	{
		printf("%s=%s\n", node->key, node->val);
		node = node->next;
	}
}

void	envp_to_env(t_env_list **my_env, char **env)
{
	t_env_node	*node;
	int	i;

	i = -1;
	init_env_list(my_env);
	while (env[++i])
	{
		node = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
		init_env_node(node, env[i]);
		add_env_node(*my_env, node);
	}
	// print_env_list(my_env);
}
