/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 12:48:42 by saan              #+#    #+#             */
/*   Updated: 2025/09/08 15:36:34 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quotes_env_key(char *line, int *idx)
{
	int	start;
	char	*temp;

	start = (*idx)++;
	while (!is_wspace(line[(*idx)]) && !is_quote(line[(*idx)]) && line[(*idx)] != '$' && line[(*idx)] != '=')
		(*idx)++;
	temp = ft_substr(line, start, *idx - start);
	(*idx)--;
	return (temp);
}

char	*get_extra_sign(char *str, char *line, int *idx)
{
	char	*res;

	(*idx) += 1;
	if (line[(*idx)] == '$')
		res = ft_strjoin_af(str, ft_strdup(""));
	else
		res = ft_strjoin_af(str, ft_strdup("$"));
	return (res);
}
