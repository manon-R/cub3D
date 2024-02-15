#include "cub.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (SUCCESS);
	while (line && line[i])
	{
		if (is_space(line[i]) == FAIL)
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	is_text_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (is_in_charset(line[i]) == FAIL)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

int	is_dir(char *str)
{
	if (ft_strcmp(str, "NO") == SUCCESS)
		return (SUCCESS);
	if (ft_strcmp(str, "SO") == SUCCESS)
		return (SUCCESS);
	if (ft_strcmp(str, "EA") == SUCCESS)
		return (SUCCESS);
	if (ft_strcmp(str, "WE") == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}

int	is_skyfloor(char *str)
{
	if (ft_strcmp(str, "F") == SUCCESS)
		return (SUCCESS);
	if (ft_strcmp(str, "C") == SUCCESS)
		return (SUCCESS);
	return (FAIL);
}
