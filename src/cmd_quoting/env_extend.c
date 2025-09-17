/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:20:35 by saan              #+#    #+#             */
/*   Updated: 2025/09/17 11:56:55 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char *get_extend(char *str, int *i, char quote, t_env_list *my_env)
{
	char	*res;
	int		start;

	start = (*i)++;
	if (ft_isdigit(str[start + 1]))
		return (extending(ft_substr(str, start, 1), my_env));
	while (str[(*i)] && !is_wspace(str[(*i)]) && !is_quote(str[(*i)]))
		(*i)++;
	if (quote == '\"')
		res = extending(ft_substr(str, start + 1, --(*i) - start), my_env);
	else
		res = ft_substr(str, start, --(*i) - start + 1);
	return (res);
}

static char	*get_extend_quote_line(char *str, int *i, char quote, t_env_list *my_env)
{
	char	*res;

	res = ft_strdup("");
	res = append_char(res, str[(*i)]);
	while (str[(*i)] && str[++(*i)] != quote)
	{
		if (str[(*i)] == '$')
		{
			if (str[(*i) + 1] == '$')
			{
				(*i) += 1;
				continue ;
			}
			res = ft_strjoin_af(res, get_extend(str, i, quote, my_env));
		}
		else
			res = append_char(res, str[(*i)]);
	}
	res = append_char(res, str[(*i)]);
	return (res);
}

static char	*get_extend_line(char *str, int *i, t_env_list *my_env)
{
	int		start;
	int		end;

	start = (*i) + 1;
	while (str[++(*i)])
	{
		if (str[(*i)] == '$')
			return (ft_strdup(""));
		if (ft_isdigit(str[(*i)]))
			return (extending(ft_substr(str, start, 1), my_env));
		while (str[(*i)] && !is_wspace(str[(*i)]) && !is_quote(str[(*i)]))
			(*i)++;
		end = --(*i);
		return (extending(ft_substr(str, start, end - start + 1), my_env));
	}
	return (ft_strdup("$"));
}

char	*extending_env(char *str, t_env_list *my_env)
{
	int	i;
	char	*res;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (is_quote(str[i]))
			res = ft_strjoin_af(res, get_extend_quote_line(str, &i, str[i], my_env));
		else if (str[i] == '$')
			res = ft_strjoin_af(res, get_extend_line(str, &i, my_env));
		else
			res = append_char(res, str[i]);
		if (!str[i])
			break ;
		i++;
	}
	return (res);
}
