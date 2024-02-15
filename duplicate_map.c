#include "cub.h"

char	**duplicate_map(t_data *data)
{
	int		size;
	int		i;
	int		index;
	char	**map_cpy;

	size = ft_tablen(data->map);
	map_cpy = malloc((size + 1) * sizeof(char *));
	if (!map_cpy)
		return (NULL);
	i = 0;
	index = 0;
	while (data->map[i])
	{
		map_cpy[index++] = \
		ft_strdup_start(data->map[i], 0, ft_strlen(data->map[i]));
		if (!map_cpy[index - 1])
			return (free_all(map_cpy), NULL);
		i++;
	}
	map_cpy[index] = 0;
	return (map_cpy);
}
