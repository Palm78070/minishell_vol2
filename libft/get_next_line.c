/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rthammat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:20:46 by rthammat          #+#    #+#             */
/*   Updated: 2022/08/13 22:06:15 by rthammat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_nextline(char *buffer, size_t l_len)
{
	char		*line;

	if (!buffer[l_len])
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[l_len] == '\n')
		l_len += 1;
	line = ft_substr(buffer, l_len, ft_strxlen(&buffer[l_len], '\0'));
	free(buffer);
	return (line);
}

char	*ft_readline(char *buffer, size_t l_len)
{
	char	*line;

	if (!buffer[0])
		return (NULL);
	if (buffer[l_len] == '\n')
		l_len += 1;
	line = ft_substr(buffer, 0, l_len);
	return (line);
}

char	*ft_readfile(int fd, char *res)
{
	char	*buffer;
	char	*tmp;
	int		byte_read;

	if (!res)
		res = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = 0;
		tmp = res;
		res = ft_strjoin(res, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	size_t		l_len;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_readfile(fd, buffer);
	if (!buffer)
		return (NULL);
	l_len = ft_strxlen(buffer, '\n');
	line = ft_readline(buffer, l_len);
	buffer = ft_nextline(buffer, l_len);
	return (line);
}
