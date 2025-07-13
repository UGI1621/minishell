/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:52:46 by saan              #+#    #+#             */
/*   Updated: 2024/11/07 22:04:12 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(char const *s, char c)
{
	int	s_word;
	int	count;

	count = 0;
	s_word = 0;
	while (*(s++))
	{
		if (!s_word && *s && *s != c)
		{
			s_word = 1;
			count++;
		}
		else if (s_word && *s == c)
			s_word = 0;
	}
	return (count);
}

void	free_res(char **res)
{
	int	i;

	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
}

void	ft_do_split(char **res, char const *s, char c, int s_idx)
{
	int		s_word;
	size_t	i;

	i = 0;
	s_word = 0;
	while (i <= ft_strlen(s))
	{
		if (!s_word && s[i] && s[i] != c)
		{
			s_word = 1;
			s_idx = i;
		}
		else if (s_word && (s[i] == c || !s[i]))
		{
			s_word = 0;
			*res = ft_substr(s, s_idx, i - s_idx);
			if (!(*res))
			{
				free_res(res);
				return ;
			}
			res++;
		}
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		word_c;
	int		s_idx;

	if (!s)
		return (NULL);
	word_c = ft_word_count(s, c);
	res = (char **)malloc(sizeof(char *) * (word_c + 1));
	if (!res)
		return (NULL);
	res[word_c] = NULL;
	s_idx = 0;
	ft_do_split(res, s, c, s_idx);
	return (res);
}
