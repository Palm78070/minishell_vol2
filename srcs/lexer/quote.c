#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

void	check_quote(char *line, int *indx)
{
	int	i;
	char	quote;

	quote = 0;
	i = *indx;
	if (line[i] && is_quote(line[i]))
	{
		quote = line[i];
		while (line[++i] && line[i] != quote)
			continue ;
	}
	*indx = i;
}

char	*check_include_quote(char *res, char *old, int *indx)
{
	int	dollar;
	int	i;
	char	quote;

	dollar = 0;
	i = *indx;
	quote = old[i];
	while (old[i] && old[i] != '$')
		++i;
	if (old[i] == '\0')
		return (res);
	res = ft_insert_char(res, old[*indx]);
	*indx += 1;
	while (old[*indx] && !is_quote(old[*indx]))
	{
		res = ft_insert_char(res, old[*indx]);
		*indx += 1;
	}
	if (old[*indx] && is_quote(old[*indx]))
		res = ft_insert_char(res, old[*indx]);
	if (old[*indx] && old[(*indx) + 1])
		*indx += 1;
	return (res);
}