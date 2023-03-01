/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psutanth <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:57:51 by psutanth          #+#    #+#             */
/*   Updated: 2023/02/23 14:18:34 by psutanth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// qflags[0] = in single quote
// qflags[1] = in double quote
static int	should_split_var(char *str, int *in_var, int qflags[2])
{
	int	temp;

	if (*str == '"' && !qflags[0])
		qflags[1] = !qflags[1];
	if (*str == '\'' && !qflags[1])
	{
		qflags[0] = !qflags[0];
		temp = *in_var;
		*in_var = 0;
		return (temp);
	}
	if (*str == '$' && !qflags[0])
	{
		*in_var = 1;
		return (1);
	}
	if (*in_var && (!ft_isalnum(*str) && *str != '_'))
	{
		*in_var = 0;
		return (1);
	}
	return (0);
}

static void	set_split_flags(int *in_var, int qflags[2], char first_char)
{
	*in_var = (first_char == '$');
	qflags[0] = (first_char == '\'');
	qflags[1] = (first_char == '"');
}

size_t	count_var_splits(char *str)
{
	size_t	i;
	int		in_var;
	int		qflags[2];

	i = (*str != '$');
	set_split_flags(&in_var, qflags, *str);
	while (*str != '\0')
	{
		i += should_split_var(str, &in_var, qflags);
		++str;
	}
	return (i);
}

char	**make_var_splits(char *str)
{
	char	**split;
	char	*current_start;
	int		in_var;
	int		qflags[2];
	size_t	i;

	split = malloc(sizeof(*split) * (count_var_splits(str) + 1));
	if (!split)
		return (NULL);
	split[count_var_splits(str)] = NULL;
	current_start = str;
	set_split_flags(&in_var, qflags, *str);
	i = 0;
	str += (*str == '$');
	while (*str != '\0')
	{
		if (should_split_var(str, &in_var, qflags))
		{
			split[i++] = ft_substr(current_start, 0, str - current_start);
			current_start = str;
		}
		++str;
	}
	split[i] = ft_substr(current_start, 0, str - current_start);
	return (split);
}
