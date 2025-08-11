/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:56:16 by saan              #+#    #+#             */
/*   Updated: 2025/08/11 11:10:31 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_node(char *s)
{
	if (!ft_strncmp(s, "<", ft_strlen(s)) ||
	!ft_strncmp(s, ">", ft_strlen(s)) || !ft_strncmp(s, ">>", ft_strlen(s)))
		return (1);
	return (0);
}

int	is_heredoc_node(char *s)
{
	if (!ft_strncmp(s, "<<", ft_strlen(s)))
		return (1);
	return (0);
}

char	*ft_strjoin_af(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}


