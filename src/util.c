/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 16:48:58 by saan              #+#    #+#             */
/*   Updated: 2025/07/27 01:46:13 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wspace(char c)
{
	return (c == 8 || c == 9 || c == 10 || c == 11
		|| c == 12 || c == 13 || c == 32);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_cutsign(char c)
{
	return (c == '|' || c == '<' || c == '>' || is_wspace(c));
}

char	*ft_join_fa(char *s1, char *s2)
{
	char	*res;
	char	*temp1;
	char	*temp2;

	temp1 = s1;
	temp2 = s2;
	res = ft_strjoin(temp1, temp2);
	free(temp1);
	free(temp2);
	return (res);
}

char	*ft_join_fs1(char *s1, char *s2)
{
	char	*res;
	char	*temp1;

	temp1 = s1;
	res = ft_strjoin(temp1, s2);
	free(temp1);
	return (res);
}
