/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:35:17 by saan              #+#    #+#             */
/*   Updated: 2025/07/15 21:06:01 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_sigs(void)
{
	if (signal(SIGINT, sa_sigint_handler) == SIG_ERR)
	{
		perror("signal SIGINT");
		exit(EXIT_FAILURE);
	}
}
