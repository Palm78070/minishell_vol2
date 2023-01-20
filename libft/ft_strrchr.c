/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:18:07 by rthammat          #+#    #+#             */
/*   Updated: 2022/02/21 23:18:23 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	last;
	int	i;

	i = -1;
	last = ft_strlen(s) - 1;
	if (c > 256)
		c -= 256;
	if (c == '\0')
	{
		s = &s[ft_strlen(s)];
		return ((char *)s);
	}
	while (last - (++i) >= 0)
	{
		if (((char *)s)[last - (i)] == c)
		{
			s = &s[last - (i)];
			return ((char *)s);
		}
	}
	s = NULL;
	return ((char *)s);
}
