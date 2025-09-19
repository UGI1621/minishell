/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 19:01:48 by saan              #+#    #+#             */
/*   Updated: 2025/09/19 20:22:48 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_and_status(pid_t *pid, int *status, int i)
{
	set_sigs_ign();
	waitpid(pid[i], status, 0);
	set_sigs();
	set_status((*status));
}

// void	free_in_error(t_cmd_list *list, t_env_list *my_env)
// {
// 	free_cmd_list(list);
// 	env_free(my_env);
// }
