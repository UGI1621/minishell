/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:19:22 by saan              #+#    #+#             */
/*   Updated: 2025/08/05 05:07:50 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dllist	*listing_cmd(t_lexer_list *list)
{
	t_dllist	*res;
	t_lexer_node	*l_node;

	res = init_cmd_list(res);
	l_node = list->head;
	while (l_node)
	{

	}
	return (res);
}
