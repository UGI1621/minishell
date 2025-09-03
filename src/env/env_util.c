/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 05:51:40 by saan              #+#    #+#             */
/*   Updated: 2025/09/02 05:52:38 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
