/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:43:14 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 21:32:58 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_set_fd(t_cmd_node *node)
{
	if (node->is_use_heredoc)
		node->in_fd = open("heredoc_temp", O_RDONLY);
	else if (node->infile && node->infile[0])
	{
		node->in_fd = b_open_infiles(node->infile, node->in_sig);
		if (node->in_fd != -1)
		{
			dup2(node->in_fd, STDIN_FILENO);
			close(node->in_fd);
		}
		else
			return (1);
	}
	if (node->outfile && node->outfile[0])
	{
		node->out_fd = b_open_outfiles(node->outfile, node->out_sig);
		if (node->out_fd != -1)
		{
			dup2(node->out_fd, STDOUT_FILENO);
			close(node->out_fd);
		}
		else
			return (1);
	}
	return (0);
}

static int	builtin_exe(t_cmd_node *node, int save_stdin, int save_stdout,
		t_env_list *my_env)
{
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
	{
		return (ft_exit(node, save_stdin, save_stdout));
	}
	return (1);
}

int	is_builtin(t_cmd_node *node)
{
	if (node->argv[0] && !ft_strcmp(node->argv[0], "echo"))
		return (1);
	if (node->argv[0] && !ft_strcmp(node->argv[0], "pwd"))
		return (1);
	if (node->argv[0] && !ft_strcmp(node->argv[0], "env"))
		return (1);
	if (node->argv[0] && !ft_strcmp(node->argv[0], "cd"))
		return (1);
	if (node->argv[0] && !ft_strcmp(node->argv[0], "export"))
		return (1);
	if (node->argv[0] && !ft_strcmp(node->argv[0], "unset"))
		return (1);
	if (node->argv[0] && !ft_strcmp(node->argv[0], "exit"))
		return (1);
	return (0);
}

void	set_iofds(int s_stdin, int s_stdout)
{
	dup2(s_stdin, STDIN_FILENO);
	dup2(s_stdout, STDOUT_FILENO);
	close(s_stdin);
	close(s_stdout);
}

int	do_builtin(t_cmd_node *node, int is_p, t_cmd_list *list, t_env_list *my_env)
{
	int	save_stdin;
	int	save_stdout;
	int	exit_code;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (is_p)
	{
		if (builtin_set_fd(node))
		{
			close(save_stdin);
			close(save_stdout);
			return (1);
		}
	}
	exit_code = builtin_exe(node, save_stdin, save_stdout, my_env);
	free_cmd_list(list, NULL);
	env_free(my_env);
	close(save_stdin);
	close(save_stdout);
	return (exit_code);
}
