/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 22:05:00 by rthammat          #+#    #+#             */
/*   Updated: 2022/02/25 22:05:19 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	if (!s || s == NULL || !f)
		return (NULL);
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	while (res[++i])
		res[i] = f(i, res[i]);
	return (res);
}
