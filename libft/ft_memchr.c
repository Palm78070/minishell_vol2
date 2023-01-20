/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:25:49 by rthammat          #+#    #+#             */
/*   Updated: 2022/03/01 16:12:46 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	i = -1;
	p = NULL;
	if (n < 1)
		return (NULL);
	p = (unsigned char *)s;
	while (++i < n)
	{
		if (p[i] == (unsigned char)c)
			return ((void *)(s + i));
	}
	return (NULL);
}
