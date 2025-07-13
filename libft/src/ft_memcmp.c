/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:12:29 by saan              #+#    #+#             */
/*   Updated: 2024/10/14 23:22:13 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	size_t			i;

	temp1 = (unsigned char *)b1;
	temp2 = (unsigned char *)b2;
	i = 0;
	while (i < len)
	{
		if (*temp1 != *temp2)
			return (*temp1 - *temp2);
		i++;
		temp1++;
		temp2++;
	}
	return (0);
}
