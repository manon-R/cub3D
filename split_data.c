#include "cub.h"
#include <stdio.h>

static int	size_map(char **content, int i)
{
	int	size;

	size = 0;
	while (content && content[i])
	{
		i++;
		size++;
	}
	return (size);
}

static int	extract_map(char **content, t_data *data)
{
	int		i;
	int		index;
	int		size;
	char	**map;

	i = 0;
	index = 0;
	while (content && content[i] && is_text_line(content[i]) == SUCCESS)
		i++;
	size = size_map(content, i);
	if (size == 0)
		return (error_mess(MAP_MISS), FAIL);
	map = malloc((size + 1) * sizeof(char *));
	if (!map)
		return (FAIL);
	while (content && content[i])
	{
		map[index++] = content[i++];
		if (!map[index - 1])
			return (free_all(map), FAIL);
	}
	map[index] = 0;
	(*data).map = map;
	return (SUCCESS);
}

static void	map_error(char **content, int index)
{
	index++;
	while (content[index])
	{
		if (is_text_line(content[index]) == FAIL && \
			is_empty_line(content[index]) == FAIL)
			return (error_mess(WRONG_CHAR), free_all(content));
		index++;
	}
	error_mess(END_MAP);
	free_all(content);
}

int	split_text_map(char **content, t_data *data)
{
	int		i;
	char	c;
	char	**text;

	i = 0;
	c = '0';
	while (content && content[i])
	{
		if (is_text_line(content[i]) == SUCCESS)
		{
			if (c == 'm')
				return (map_error(content, i), FAIL);
			text = ft_split(content[i], " \t\n");
			if (!text)
				return (error_mess(MALLOC_ERR), FAIL);
			if (check_text(data, text) == FAIL)
				return (free_all(text), text = NULL, FAIL);
			c = 't';
			free_all(text);
			text = NULL;
		}
		else
			c = 'm';
		i++;
	}
	return (extract_map(content, data));
}
