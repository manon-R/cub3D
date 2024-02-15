#include "cub.h"

char	*ft_strcpy(char *buffer, char *tmp)
{
	int	i;

	i = 0;
	while (tmp && tmp[i])
	{
		buffer[i] = tmp[i];
		i++;
	}
	buffer[i] = '\0';
	return (free(tmp), buffer);
}
