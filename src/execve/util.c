/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:43:14 by saan              #+#    #+#             */
/*   Updated: 2025/09/04 00:57:10 by saan             ###   ########.fr       */
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
	if (!ft_strncmp(node->argv[0], "echo", ft_strlen(node->argv[0])))
		return (1);
	if (!ft_strncmp(node->argv[0], "pwd", ft_strlen(node->argv[0])))
		return (1);
	if (!ft_strncmp(node->argv[0], "env", ft_strlen(node->argv[0])))
		return (1);
	if (!ft_strncmp(node->argv[0], "cd", ft_strlen(node->argv[0])))
		return (1);
	if (!ft_strncmp(node->argv[0], "export", ft_strlen(node->argv[0])))
		return (1);
	if (!ft_strncmp(node->argv[0], "unset", ft_strlen(node->argv[0])))
		return (1);
	if (!ft_strncmp(node->argv[0], "exit", ft_strlen(node->argv[0])))
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
	if (!ft_strncmp(node->argv[0], "echo", ft_strlen(node->argv[0])))
		return (ft_echo(node, my_env, save_stdin, save_stdout));
	else if (!ft_strncmp(node->argv[0], "pwd", ft_strlen(node->argv[0])))
		return (ft_pwd(node, my_env, save_stdin, save_stdout));
	else if (!ft_strncmp(node->argv[0], "env", ft_strlen(node->argv[0])))
		return (ft_env(node, my_env, save_stdin, save_stdout));
	else if (!ft_strncmp(node->argv[0], "cd", ft_strlen(node->argv[0])))
		return (0);
	else if (!ft_strncmp(node->argv[0], "export", ft_strlen(node->argv[0])))
		return (0);
	else if (!ft_strncmp(node->argv[0], "unset", ft_strlen(node->argv[0])))
		return (0);
	else if (!ft_strncmp(node->argv[0], "exit", ft_strlen(node->argv[0])))
		return (ft_exit(node, save_stdin, save_stdout));
	// set_iofds(save_stdin, save_stdout);
	return (0);
}
