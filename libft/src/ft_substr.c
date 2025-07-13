/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:01:00 by saan              #+#    #+#             */
/*   Updated: 2024/10/29 20:23:59 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*temp;

	s_len = ft_strlen(s);
	if (s_len - start < len)
		len = s_len - start;
	if (s_len < start)
	{
		temp = (char *)malloc(sizeof(char) * 1);
		if (!temp)
			return (0);
		temp[0] = '\0';
		return (temp);
	}
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return (0);
	ft_strlcpy(temp, &s[start], len + 1);
	return (temp);
}
