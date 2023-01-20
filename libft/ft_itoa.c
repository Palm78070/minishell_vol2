/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:15:03 by rthammat          #+#    #+#             */
/*   Updated: 2022/02/22 01:15:20 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_intsize(int n)
{
	int	res;

	res = 0;
	if (n < 0 && ++res)
		n *= (-1);
	while (n > 0 && ++res)
		n /= 10;
	return (res);
}

static char	*check_num_min(char *s, int n)
{
	char	*res;

	res = s;
	if (n == -2147483648)
		res = ft_strdup("-2147483648");
	if (n == 0)
		res = ft_strdup("0");
	return (res);
}

char	*ft_itoa(int n)
{
	int		len_rev;
	int		indx;
	char	*res;

	len_rev = get_intsize(n) - 1;
	indx = 0;
	res = check_num_min(NULL, n);
	if (res != NULL)
		return (res);
	res = (char *)malloc((len_rev + 2) * sizeof(char));
	if (!res)
		return (NULL);
	res[get_intsize(n)] = '\0';
	if (n < 0 && ++indx)
	{
		n *= -1;
		res[0] = '-';
	}
	while (len_rev >= indx)
	{
		res[len_rev--] = (n % 10) + '0';
		n /= 10;
	}
	return (res);
}
