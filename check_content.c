#include "cub.h"

int	check_all_elem(t_data *data)
{
	if (!data->dir_tab.no)
		return (error_mess(NO_MISS), FAIL);
	if (!data->dir_tab.so)
		return (error_mess(SO_MISS), FAIL);
	if (!data->dir_tab.ea)
		return (error_mess(EA_MISS), FAIL);
	if (!data->dir_tab.we)
		return (error_mess(WE_MISS), FAIL);
	if (!data->fc_tab.f)
		return (error_mess(F_MISS), FAIL);
	if (!data->fc_tab.c)
		return (error_mess(C_MISS), FAIL);
	return (SUCCESS);
}

int	check_text(t_data *data, char **text)
{
	if (is_dir(text[0]) == SUCCESS)
	{
		if (is_valid_texture_direction(text) == FAIL)
			return (FAIL);
	}
	else if (is_skyfloor(text[0]) == SUCCESS)
	{
		if (is_valid_color_format(text) == FAIL)
			return (FAIL);
	}
	else
		return (error_mess(INVALID_TEXT), FAIL);
	if (init_text(data, text) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	check_valid_char(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map && data->map[i])
	{
		j = 0;
		if (is_empty_line(data->map[i]) == SUCCESS)
			return (error_mess(EMPTY_LINE), FAIL);
		while (data->map[i][j])
		{
			if (is_in_charset(data->map[i][j]) == FAIL)
				return (error_mess(WRONG_CHAR), FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_dfs(char **map_cpy)
{
	int	i;
	int	j;

	i = 0;
	while (map_cpy[i])
	{
		j = 0;
		while (map_cpy[i][j])
		{
			if (map_cpy[i][j] != '1' && map_cpy[i][j] != 'X' && \
				is_space(map_cpy[i][j]) == FAIL)
				return (error_mess(INVALID_DFS), FAIL);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map(t_data *data)
{
	char	**map_cpy;

	//check size map / taille de la window Ou definir une taille max
	if (check_valid_char(data) == FAIL)
		return (FAIL);
	map_cpy = duplicate_map(data);
	if (!map_cpy)
		return (FAIL);
	ft_dfs(data->player.pos.y, data->player.pos.x, map_cpy);
	if (check_dfs(map_cpy) == FAIL)
		return (free_all(map_cpy), FAIL);
	free_all(map_cpy);
	if (check_space(data) == FAIL)
		return (error_mess(INVALID_SPACES), FAIL);
	return (SUCCESS);
}
