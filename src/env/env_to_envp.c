/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:32:45 by saan              #+#    #+#             */
/*   Updated: 2025/08/28 17:43:47 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_to_envp(t_env_list *my_env)
{
	char	**res;
	char	*temp;
	t_env_node	*node;
	int	i;

	i = -1;
	node = my_env->head;
	res = (char **)ft_calloc(my_env->size + 1, sizeof(char *));
	while (node && ++i < my_env->size)
	{
		temp = ft_strdup("");
		temp = ft_strjoin_af(temp, ft_strdup(node->key));
		temp = ft_strjoin_af(temp, ft_strdup("="));
		temp = ft_strjoin_af(temp, ft_strdup(node->val));
		res[i] = temp;
		node = node->next;
	}
	res[i + 1] = NULL;
	return (res);
}
