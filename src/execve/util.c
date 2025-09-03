/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:43:14 by saan              #+#    #+#             */
/*   Updated: 2025/09/04 05:04:04 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	builtin_set_fd(t_cmd_node *node)
{
	if (node->is_use_heredoc)
		node->in_fd = open("heredoc_temp", O_RDONLY);
	else
		node->in_fd = open_infiles(node->infile);
	if (node->in_fd != -1)
	{
		dup2(node->in_fd , STDIN_FILENO);
		close(node->in_fd);
	}
	node->out_fd = open_outfiles(node->outfile, node->out_sig);
	if (node->out_fd != -1)
	{
		dup2(node->out_fd, STDOUT_FILENO);
		close(node->out_fd);
	}
}

int	is_builtin(t_cmd_node *node)
{
	if (!ft_strcmp(node->argv[0], "echo"))
		return (1);
	if (!ft_strcmp(node->argv[0], "pwd"))
		return (1);
	if (!ft_strcmp(node->argv[0], "env"))
		return (1);
	if (!ft_strcmp(node->argv[0], "cd"))
		return (1);
	if (!ft_strcmp(node->argv[0], "export"))
		return (1);
	if (!ft_strcmp(node->argv[0], "unset"))
		return (1);
	if (!ft_strcmp(node->argv[0], "exit"))
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

int	do_builtin(t_cmd_node *node, int is_p, t_env_list *my_env)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (is_p)
		builtin_set_fd(node);
	if (!ft_strcmp(node->argv[0], "echo"))
		return (ft_echo(node, my_env, save_stdin, save_stdout));
	else if (!ft_strcmp(node->argv[0], "pwd"))
		return (ft_pwd(node, my_env, save_stdin, save_stdout));
	else if (!ft_strcmp(node->argv[0], "env"))
		return (ft_env(node, my_env, save_stdin, save_stdout));
	else if (!ft_strcmp(node->argv[0], "cd"))
		return (0);
	else if (!ft_strcmp(node->argv[0], "export"))
		return (ft_export(node, save_stdin, save_stdout, my_env));
	else if (!ft_strcmp(node->argv[0], "unset"))
		return (0);
	else if (!ft_strcmp(node->argv[0], "exit"))
		return (ft_exit(node, save_stdin, save_stdout));
	// set_iofds(save_stdin, save_stdout);
	return (0);
}
