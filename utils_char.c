#include "cub.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (SUCCESS);
	return (FAIL);
}

int	is_in_charset(char c)
{
	if (is_space(c) == SUCCESS || c == '0' || c == '1' || \
		c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (SUCCESS);
	return (FAIL);
}

int	is_pov(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (SUCCESS);
	return (FAIL);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
