/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:16:54 by saan              #+#    #+#             */
/*   Updated: 2024/10/22 14:22:25 by saan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*big_temp;
	char	*lil_temp;
	size_t	i;
	size_t	i_temp;

	i = 0;
	if (!ft_strlen(little))
		return ((char *)big);
	while (*big && (i < len))
	{
		if (*big == *little)
		{
			big_temp = (char *)big;
			lil_temp = (char *)little;
			i_temp = i;
			while (*lil_temp && (*(big_temp++) == *lil_temp)
				&& (i_temp++ < len))
				lil_temp++;
			if (!*lil_temp)
				return ((char *)big);
		}
		i++;
		big++;
	}
	return (NULL);
}
