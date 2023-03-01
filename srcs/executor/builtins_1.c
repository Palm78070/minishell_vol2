/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 09:13:07 by psutanth          #+#    #+#             */
/*   Updated: 2023/03/01 11:58:38 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	char	*this_path;

	this_path = realpath(".", NULL);
	printf("%s\n", this_path);
	free(this_path);
	return (0);
}

int	builtin_echo(char **argv)
{
	char	newline;
	size_t	i;

	if (argv[1] == NULL)
	{
		printf("\n");
		return (0);
	}
	newline = 1;
	i = (ft_strncmp(argv[1], "-n", 3) == 0);
	if (i)
		newline = 0;
	while (argv[++i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
	}
	if (newline)
		printf("\n");
	return (0);
}
