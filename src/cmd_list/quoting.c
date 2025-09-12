/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:15:21 by saan              #+#    #+#             */
/*   Updated: 2025/09/12 08:41:43 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extending(char *s, t_env_list *my_env)
{
	if (s && !s[0])
	{
		free(s);
		return (ft_strdup("$"));
	}
	if (is_expandable(s))
		return (extend_res(s, my_env));
	else
		return (no_extend_res(s));
	return (ft_strdup(""));
}

static char	*env_extend(char *s, char quote, t_env_list *my_env)
{
	char	*res;
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
			res = ft_strjoin_af(res, extending(ft_substr(s, i - j, j), my_env));
			break ;
		}
	}
	free(s);
	return (res);
}

static char	*get_quotes(char *line, int *idx, int is_extend, t_env_list *my_env)
{
	char	quote;
	char	*temp;
	char	*res;

	quote = line[(*idx)];
	res = ft_strdup("");
	while (line[++(*idx)] != quote)
	{
		if (line[(*idx)] == '$' && line[(*idx) + 1] != '$' && line[(*idx) + 1] != quote)
		{
			temp = get_quotes_env_key(line, idx);
			if (is_extend && ft_strchr(temp, '$'))
				res = ft_strjoin_af(res, env_extend(temp, quote, my_env));
			else
				res = ft_strjoin_af(res, temp);
		}
		else if (line[(*idx)] == '$' && (line[(*idx) + 1] == '$' || line[(*idx)] == quote))
			res = get_extra_sign(res, line, idx);
		else
			res = append_char(res, line[*idx]);
	}
	return (res);
}

static char	*get_words(char *line, int *idx, int is_extend, t_env_list *my_env)
{
	int	start;
	char	*temp;

	if (line[*idx] == '$' && line[*idx + 1] == '$')
	{
		*idx += 1;
		return (ft_strdup(""));
	}
	if (line[*idx] == '$' && !line[*idx + 1])
		return (ft_strdup("$"));
	start = (*idx)++;
	while(line[*idx] && !is_quote(line[*idx]) && line[*idx] != '=' && line[*idx] != '$')
		(*idx)++;
	if (is_quote(line[*idx]) || line[*idx] == '=' || line[*idx] == '$')
		(*idx)--;
	if (!line[*idx])
		temp = ft_substr(line, start, *idx - start);
	else
		temp = ft_substr(line, start, *idx - start + 1);
	if (is_extend && ft_strchr(temp, '$'))
		return (env_extend(temp, '\"', my_env));
	return (temp);
}

char	*cal_quotes(char *line, int	is_extend, t_env_list *my_env)
{
	char	*res;
	char	*temp;
	int		i;

	i = -1;
	res = ft_strdup("");
	while(line[++i])
	{
		if (is_quote(line[i]))
			temp = get_quotes(line, &i, is_extend, my_env);
		else if (line[i] == '=')
			temp = ft_strdup("=");
		else
			temp = get_words(line, &i, is_extend, my_env);
		res = ft_strjoin_af(res, temp);
		if(!line[i])
			break ;
	}
	free(line);
	return (res);
}
