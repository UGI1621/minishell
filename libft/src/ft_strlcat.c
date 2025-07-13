/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:47:35 by saan              #+#    #+#             */
/*   Updated: 2024/11/18 17:34:32 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t destsize)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	dest_idx;
	size_t	src_idx;

	dest_len = ft_strlen(dest);
	dest_idx = dest_len;
	src_len = ft_strlen(src);
	src_idx = 0;
	while (src[src_idx] && dest_len + src_idx + 1 < destsize)
	{
		dest[dest_idx] = src[src_idx];
		src_idx++;
		dest_idx++;
	}
	if (dest_len < destsize)
	{
		dest[dest_idx] = '\0';
		return (src_len + dest_len);
	}
	return (src_len + destsize);
}
