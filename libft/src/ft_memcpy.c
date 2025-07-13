/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <saan@student.42gyeongsan.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:01:27 by saan              #+#    #+#             */
/*   Updated: 2024/11/30 07:50:49 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char	*temp;
	unsigned char	*s;

	if (dest == src)
		return (dest);
	temp = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (len--)
		*temp++ = *s++;
	return (dest);
}
