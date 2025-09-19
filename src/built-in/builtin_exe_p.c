/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exe_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:12:54 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 02:38:44 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	builtin_exe_p(t_cmd_list *list, int save_stdin, int save_stdout,
		t_env_list *my_env)
{
	t_cmd_node	*node;

	node = list->head;
	if (!ft_strcmp(node->argv[0], "echo"))
		return (ft_echo(node, save_stdin, save_stdout));
	else if (!ft_strcmp(node->argv[0], "pwd"))
		return (ft_pwd(node, save_stdin, save_stdout));
	else if (!ft_strcmp(node->argv[0], "env"))
		return (ft_env(node, my_env, save_stdin, save_stdout));
	else if (!ft_strcmp(node->argv[0], "cd"))
		return (ft_cd(node, save_stdin, save_stdout, my_env));
	else if (!ft_strcmp(node->argv[0], "export"))
		return (ft_export(node, save_stdin, save_stdout, my_env));
	else if (!ft_strcmp(node->argv[0], "unset"))
		return (ft_unset(node, save_stdin, save_stdout, my_env));
	else if (!ft_strcmp(node->argv[0], "exit"))
		return (ft_exit_p(list, save_stdin, save_stdout, my_env));
	return (1);
}

int	do_builtin_p(t_cmd_list *list, int is_p, t_env_list *my_env)
{
	int	save_stdin;
	int	save_stdout;
	int	exit_code;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (is_p)
	{
		if (builtin_set_fd(list->head))
		{
			close(save_stdin);
			close(save_stdout);
			return (1);
		}
	}
	exit_code = builtin_exe_p(list, save_stdin, save_stdout, my_env);
	close(save_stdin);
	close(save_stdout);
	return (exit_code);
}
