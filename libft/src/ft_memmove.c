/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:08:48 by saan              #+#    #+#             */
/*   Updated: 2024/10/29 20:07:28 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*temp;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	temp = dest;
	s = (unsigned char *)src;
	if (dest <= src)
	{
		while (len--)
			*temp++ = *s++;
	}
	else
	{
		temp += len;
		s += len;
		while (len--)
			*--temp = *--s;
	}
	return (dest);
}
