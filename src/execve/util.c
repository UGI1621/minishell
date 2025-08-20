/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 15:43:14 by saan              #+#    #+#             */
/*   Updated: 2025/08/20 18:22:00 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	p_builtin_set_fd(t_cmd_node *node)
{
	if (node->is_use_heredoc)
		node->in_fd = *node->heredoc_fd;
	else
		node->in_fd = open_infiles(node->infile);
	node->out_fd = open_outfiles(node->outfile, node->out_sig);
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
	// if (!ft_strncmp(node->argv[0], "exit", ft_strlen(node->argv[0])))
	// 	return (1);
	return (0);
}

void	do_builtin(t_cmd_node *node)
{
	p_builtin_set_fd(node);
	if (!ft_strncmp(node->argv[0], "echo", ft_strlen(node->argv[0])))
		ft_echo(node);
	else if (!ft_strncmp(node->argv[0], "pwd", ft_strlen(node->argv[0])))
		return ;
	else if (!ft_strncmp(node->argv[0], "env", ft_strlen(node->argv[0])))
		return ;
	else if (!ft_strncmp(node->argv[0], "cd", ft_strlen(node->argv[0])))
		return ;
	else if (!ft_strncmp(node->argv[0], "export", ft_strlen(node->argv[0])))
		return ;
	else if (!ft_strncmp(node->argv[0], "unset", ft_strlen(node->argv[0])))
		return ;
	// if (!ft_strncmp(node->argv[0], "exit", ft_strlen(node->argv[0])))
	// 	return ;
}
