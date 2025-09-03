/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:15:21 by saan              #+#    #+#             */
/*   Updated: 2025/08/29 14:38:24 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extending(char *s)
{
	char	*res;
	char	*temp;

	if (ft_strlen(s) == 1 && !ft_strncmp(s, "?", 1))
	{
		free(s);
		return(ft_itoa(g_sigs.exit_code));
	}
	temp = getenv(s);
	if (!temp)
	{
		temp = ft_strdup("");
		free(s);
		return (temp);
	}
	res = ft_strdup(temp);
	free(s);
	return (res);
}

static char	*env_extend(char *s, char quote)
{
	char	*res;
	char	*temp;
	int		i;
	int		j;

	if (quote == '\'')
		return (s);
	i = -1;
	res = ft_strdup("");
	while (s[++i])
	{
		if (s[i] == '$')
		{
			res = ft_strjoin_af(res, ft_substr(s, 0, i));
			j = 0;
			while (s[++i] && !is_wspace(s[i]) && s[i] != quote)
				j++;
			res = ft_strjoin_af(res, extending(ft_substr(s, i - j, j)));
			break ;
		}
	}
	free(s);
	return (res);
}

static char	*get_quotes(char *line, int *idx, int is_heredoc)
{
	char	quote;
	int		start;
	int		end;
	char	*temp;

	quote = line[*idx];
	start = (*idx)++;
	while (line[(*idx)])
	{
		if (line[*idx] == quote)
		{
			temp = ft_substr(line, start + 1, *idx - start - 1);
			if (!is_heredoc && ft_strchr(temp, '$'))
				return (env_extend(temp, quote));
			return(temp);
		}
		(*idx)++;
	}
	return (NULL);
}

static char	*get_words(char *line, int *idx, int is_heredoc)
{
	int	start;
	int	end;
	char	*temp;

	start = (*idx);
	while(line[*idx] && !is_quote(line[*idx]))
		(*idx)++;
	if (is_quote(line[*idx]))
		(*idx)--;
	if (!line[*idx])
		temp = ft_substr(line, start, *idx - start);
	else
		temp = ft_substr(line, start, *idx - start + 1);
	if (!is_heredoc && ft_strchr(temp, '$'))
		return (env_extend(temp, '\"'));
	return (temp);
}

char	*cal_quotes(char *line, int	is_heredoc)
{
	char	*res;
	char	*temp;
	int		i;

	i = -1;
	res = ft_strdup("");
	while(line[++i])
	{
		if (is_quote(line[i]))
			temp = get_quotes(line, &i, is_heredoc);
		else
			temp = get_words(line, &i, is_heredoc);
		res = ft_strjoin_af(res, temp);
		if(!line[i])
			break ;
	}
	free(line);
	return (res);
}
