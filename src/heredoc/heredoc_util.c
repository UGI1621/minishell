/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:42:22 by saan              #+#    #+#             */
/*   Updated: 2025/09/20 00:47:20 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_del_field(t_cmd_node *cn, t_lexer_node *ln)
{
	int		len;
	int		i;
	char	**new;

	len = 0;
	while (cn->infile && cn->infile[len])
		len++;
	new = (char **)ft_calloc(len + 2, sizeof(char *));
	i = 0;
	while (cn->infile && cn->infile[i])
	{
		new[i] = ft_strdup(cn->infile[i]);
		i++;
	}
	new[i] = ft_strdup(ln->str);
	new[i + 1] = NULL;
	set_in_sig(cn, "<<");
	free_2ptr(cn->infile);
	cn->infile = new;
}

void	update_heredoc_field(t_cmd_node *cn, t_lexer_node **ln)
{
	(*ln) = (*ln)->next;
	set_del_field(cn, (*ln));
	cn->is_use_heredoc = 1;
}
