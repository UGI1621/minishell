/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:40:15 by saan              #+#    #+#             */
/*   Updated: 2025/09/18 14:43:59 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_n_sig(t_cmd_node *node, int *i, int *flag)
{
	int	idx;

	while (node->argv[(*i)][0] == '-' && node->argv[(*i)][1] == 'n')
	{
		idx = 2;
		while (node->argv[(*i)][idx] && node->argv[(*i)][idx] == 'n' && !is_wspace(node->argv[(*i)][idx]))
			idx++;
		if (node->argv[(*i)][idx])
			break ;
		else
			(*flag) = 0;
		(*i)++;
	}
}

int	ft_echo(t_cmd_node *node, int save_stdin, int save_stdout)
{
	int	i;
	int	flag;

	i = 1;
	flag = 1;
	check_n_sig(node, &i, &flag);
	while (node->argv[i])
	{
		ft_putstr_fd(node->argv[i], STDOUT_FILENO);
		if (node->argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	set_iofds(save_stdin, save_stdout);
	return (0);
}
