/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:17 by saan              #+#    #+#             */
/*   Updated: 2025/07/28 15:36:04 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sigs(void)
{
	if (signal(SIGINT, s_sigint_handler) == SIG_ERR)
	{
		perror("signal SIGINT");
		exit(EXIT_FAILURE);
	}
	if (signal(SIGQUIT, s_sigquit_handler) == SIG_ERR)
	{
		perror("signal SIGQUIT");
		exit(EXIT_FAILURE);
	}
}

t_lexer_list	*init_lexer_list(t_lexer_list *list)
{
	list = (t_lexer_list *)ft_calloc(1, sizeof(t_lexer_list));
	list->head = NULL;
	list->tail = NULL;
	return (list);
}
