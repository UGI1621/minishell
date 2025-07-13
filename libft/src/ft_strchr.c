/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:21:41 by saan              #+#    #+#             */
/*   Updated: 2024/10/29 20:23:05 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*temp;
	char	c_temp;

	temp = (char *)s;
	c_temp = (char)c;
	while (*temp)
	{
		if (*temp == c_temp)
			return (temp);
		temp++;
	}
	if (*temp != c_temp)
		return (NULL);
	return (temp);
}
