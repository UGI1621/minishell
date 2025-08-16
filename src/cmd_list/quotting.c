/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:15:21 by saan              #+#    #+#             */
/*   Updated: 2025/08/16 12:53:14 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <stdint.h>

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;
// 	char	*temp;

// 	len = 0;
// 	if (!s || !*s)
// 		return (len);
// 	temp = (char *)s;
// 	while (temp[len])
// 		len++;
// 	return (len);
// }

// size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i] && i + 1 < destsize)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	if (destsize != 0)
// 		dest[i] = '\0';
// 	return (ft_strlen(src));
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	s_len;
// 	char	*temp;

// 	s_len = ft_strlen(s);
// 	if (s_len - start < len)
// 		len = s_len - start;
// 	if (s_len < start)
// 	{
// 		temp = (char *)malloc(sizeof(char) * 1);
// 		if (!temp)
// 			return (0);
// 		temp[0] = '\0';
// 		return (temp);
// 	}
// 	temp = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!temp)
// 		return (0);
// 	ft_strlcpy(temp, &s[start], len + 1);
// 	return (temp);
// }

// char	*ft_strdup(const char *str)
// {
// 	char	*temp;
// 	size_t	len;

// 	len = ft_strlen(str);
// 	temp = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!temp)
// 		return (NULL);
// 	ft_strlcpy(temp, str, len + 1);
// 	return (temp);
// }

// size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
// {
// 	size_t	dest_len;
// 	size_t	src_len;
// 	size_t	dest_idx;
// 	size_t	src_idx;

// 	dest_len = ft_strlen(dest);
// 	dest_idx = dest_len;
// 	src_len = ft_strlen(src);
// 	src_idx = 0;
// 	while (src[src_idx] && dest_len + src_idx + 1 < destsize)
// 	{
// 		dest[dest_idx] = src[src_idx];
// 		src_idx++;
// 		dest_idx++;
// 	}
// 	if (dest_len < destsize)
// 	{
// 		dest[dest_idx] = '\0';
// 		return (src_len + dest_len);
// 	}
// 	return (src_len + destsize);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*res;
// 	size_t	s1_len;
// 	size_t	s2_len;
// 	size_t	total_len;

// 	s1_len = ft_strlen(s1);
// 	s2_len = ft_strlen(s2);
// 	total_len = s1_len + s2_len;
// 	res = (char *)malloc((total_len + 1) * sizeof(char));
// 	if (!res)
// 		return (0);
// 	ft_strlcpy(res, s1, total_len + 1);
// 	ft_strlcat(res, s2, total_len + 1);
// 	return (res);
// }

// char	*ft_strjoin_af(char *s1, char *s2)
// {
// 	char	*res;

// 	res = ft_strjoin(s1, s2);
// 	free(s1);
// 	free(s2);
// 	return (res);
// }

// int	is_quote(char c)
// {
// 	return (c == '\'' || c == '\"');
// }

// void	*ft_memset(void *dest, int c, size_t len)
// {
// 	size_t			i;
// 	unsigned char	*temp;

// 	temp = (unsigned char *)dest;
// 	i = 0;
// 	while (i < len)
// 	{
// 		*temp = (unsigned char)c;
// 		temp++;
// 		i++;
// 	}
// 	return (dest);
// }

// void	ft_bzero(void *b, size_t len)
// {
// 	ft_memset(b, 0, len);
// }

// void	*ft_calloc(size_t number, size_t size)
// {
// 	void	*temp;

// 	if (size && (number > SIZE_MAX / size))
// 		return (NULL);
// 	temp = (void *)malloc(number * size);
// 	if (!temp)
// 		return (NULL);
// 	ft_bzero(temp, number * size);
// 	return (temp);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	char	*temp;
// 	char	c_temp;

// 	temp = (char *)s;
// 	c_temp = (char)c;
// 	while (*temp)
// 	{
// 		if (*temp == c_temp)
// 			return (temp);
// 		temp++;
// 	}
// 	if (*temp != c_temp)
// 		return (NULL);
// 	return (temp);
// }

// int	is_wspace(char c)
// {
// 	return (c == 8 || c == 9 || c == 10 || c == 11
// 		|| c == 12 || c == 13 || c == 32);
// }

/********************************************************/

static char	*extending(char *s)
{
	char	*res;
	char	*temp;

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
			printf("res :%s\n",res);
			j = 0;
			while (s[++i] && !is_wspace(s[i]) && !is_quote(s[i]))
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

	start = (*idx)++;
	while(line[*idx] && !is_quote(line[*idx]))
		(*idx)++;
	if (is_quote(line[*idx]))
		(*idx)--;
	temp = ft_substr(line, start, *idx - start);
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
	}
	free(line);
	return (res);
}

// int	main(void)
// {
// 	char	*temp = cal_quotes("$HOME\"123 \'$HOME\' 123\"\'$HOME\'", 0);
// 	printf("cal_quote : %s\n", temp);
// 	free(temp);
// 	return (0);
// }
