/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:56:16 by saan              #+#    #+#             */
/*   Updated: 2025/08/09 16:31:15 by saan             ###   ########.fr       */
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

char	*get_quotes(char *line, int *idx)
{
	char	quote;
	int		start;
	int		end;

	quote = line[*idx];
	start = (*idx)++;
	while (line[(*idx)])
	{
		if (line[*idx] == quote)
				return (ft_substr(line, start, *idx - start + 1));
		(*idx)++;
	}
	return (NULL);
}

char	*get_words(char *line, int *idx)
{
	int	start;
	int	end;

	start = (*idx)++;
	while(line[*idx]) // 만약 quote라면?
		(*idx)++;
	return (NULL);
}

char	*cal_quotes(char *line)
{
	char	*res;
	char	*temp;
	int		i;

	i = -1;
	res = ft_strdup("");
	while(line[++i])
	{
		if (is_quote(line[i]))
			temp = get_quotes(line, &i);
		else
			temp = get_words(line, &i);
		// temp = extend_line(temp);
		res = ft_strjoin_af(res, temp);
	}
	return (res);
}
