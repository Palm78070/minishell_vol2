/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:12:25 by rthammat          #+#    #+#             */
/*   Updated: 2022/02/21 23:12:39 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c > 256)
		c -= 256;
	if (c == '\0')
	{
		while (((char *)s)[i] != '\0')
			++i;
		s = &s[i];
		return ((char *)s);
	}
	while (s[i])
	{
		if (((char *)s)[i] == c)
		{
			s = &s[i];
			return ((char *)s);
		}
		++i;
	}
	s = NULL;
	return ((char *)s);
}
