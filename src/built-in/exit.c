/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:41:54 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 01:36:19 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_need_digit(t_cmd_list *list, t_env_list *my_env, char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
	if (list)
		free_cmd_list(list, NULL);
	if (my_env)
		env_free(my_env);
	exit(2);
}

static int	is_only_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			i++;
			continue ;
		}
		else
			return (0);
	}
	if (is_out_of_longlong(str))
		return (0);
	return (1);
}

static int	write_too_many(int sstdin, int sstdout)
{
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	set_iofds(sstdin, sstdout);
	return (1);
}

int	ft_exit_p(t_cmd_list *list, int save_stdin, int save_stdout,
		t_env_list *my_env)
{
	int			i;
	t_cmd_node	*node;

	node = list->head;
	i = 0;
	ft_putendl_fd("exit", 1);
	while (node->argv[i])
		i++;
	if (node->argv[1] && !is_only_digit(node->argv[1]))
	{
		set_iofds(save_stdin, save_stdout);
		write_need_digit(list, my_env, node->argv[1]);
	}
	if (i >= 3)
		return (write_too_many(save_stdin, save_stdout));
	if (i == 2)
	{
		set_iofds(save_stdin, save_stdout);
		i = ft_atoi(node->argv[1]);
		free_cmd_list(list, NULL);
		env_free(my_env);
		exit(i);
	}
	return (0);
}

int	ft_exit(t_cmd_node *node, int save_stdin, int save_stdout)
{
	int	i;

	i = 0;
	while (node->argv[i])
		i++;
	if (node->argv[1] && !is_only_digit(node->argv[1]))
	{
		set_iofds(save_stdin, save_stdout);
		write_need_digit(NULL, NULL, node->argv[1]);
	}
	if (i >= 3)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		set_iofds(save_stdin, save_stdout);
		return (1);
	}
	if (i == 2)
	{
		set_iofds(save_stdin, save_stdout);
		exit(ft_atoi(node->argv[1]));
	}
	exit(0);
	return (0);
}
