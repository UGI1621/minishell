/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 04:47:49 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 12:53:57 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_sigs(void)
{
	set_techo_off();
	set_sigint_handler();
	set_sigquit_handler();
}

void	set_sigs_ign(void)
{
	set_sigint_ign();
	set_sigquit_ign();
}

void	set_sigs_dfl(void)
{
	set_techo_on();
	set_sigint_dfl();
	set_sigquit_dfl();
}

void	set_sigs_heredoc(void)
{
	set_sigint_handler_heredoc();
	set_sigquit_ign();
}
