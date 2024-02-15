#include "cub.h"

void	free_all(char **result)
{
	int	i;

	i = 0;
	while (result && result[i])
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	if (result)
	{
		free(result);
		result = NULL;
	}
}

void	clean(int fd, char **content, t_data *data)
{
	free_all(content);
	free((*data).map);
	close(fd);
}
