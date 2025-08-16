/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:02:02 by saan              #+#    #+#             */
/*   Updated: 2025/08/16 16:08:48 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		list_size(t_dllist *list)
{
	t_cmd_node *node;
	int			i;

	i = 0;
	node = list->head;
	while (node)
	{
		i++;
		node = node->next;
	}
	return (i);
}

void	process_cmd_exe(t_dllist *list)
{
	pid_t	*pid;
	int		size;
	int		i;

	size = list_size(list);
	if (!size)
		return ;
	pid = (pid_t *)ft_calloc(size, sizeof(pid_t));

}
