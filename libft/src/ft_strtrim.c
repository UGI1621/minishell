/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 17:45:31 by saan              #+#    #+#             */
/*   Updated: 2024/10/22 18:02:55 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_set(char c, char *set)
{
	int	len;
	int	i;

	len = ft_strlen(set);
	i = -1;
	while (++i < len)
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s_i;
	int		e_i;
	int		total_len;
	char	*res;

	s_i = 0;
	e_i = ft_strlen(s1) - 1;
	while (check_set(s1[s_i], (char *)set))
		s_i++;
	while (check_set(s1[e_i], (char *)set))
		e_i--;
	total_len = e_i - s_i + 1;
	res = ft_substr(s1, s_i, total_len);
	return (res);
}
