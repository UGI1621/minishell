/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sig_ign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 05:38:04 by saan              #+#    #+#             */
/*   Updated: 2025/09/08 05:38:21 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigint_ign(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		perror("signal SIGINT");
		exit(EXIT_FAILURE);
	}
}

void	set_sigquit_ign(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal SIGQUIT");
		exit(EXIT_FAILURE);
	}
}
