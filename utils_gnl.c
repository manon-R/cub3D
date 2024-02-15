#include "cub.h"

int	find_nl(char *buffer)
{
	int	i;

	if (!buffer)
		return (0);
	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*result;

	result = s;
	while (n)
	{
		*(result++) = 0;
		n--;
	}
}
