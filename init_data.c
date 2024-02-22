#include "cub.h"

void	init_data(t_data *data)
{
	data->map = NULL;
	data->win = NULL;
	data->img_ptr = NULL;
	data->dir_tab.no = NULL;
	data->dir_tab.so = NULL;
	data->dir_tab.ea = NULL;
	data->dir_tab.we = NULL;
	data->dir_text.n.img_p = NULL;
	data->dir_text.s.img_p = NULL;
	data->dir_text.e.img_p = NULL;
	data->dir_text.w.img_p = NULL;
	data->fc_tab.f = NULL;
	data->fc_tab.f_color = 0x0;
	data->fc_tab.c = NULL;
	data->fc_tab.c_color = 0x0;
	data->player.pov = '0';
}

t_vector	set_dir(char c)
{
	if (c == 'N')
		return ((t_vector){1, 0});
	if (c == 'S')
		return ((t_vector){-1, 0});
	if (c == 'E')
		return ((t_vector){0, 1});
	return ((t_vector){0, -1});
}

t_vector	set_plane(char c)
{
	if (c == 'N')
		return ((t_vector){0, 0.66});
	if (c == 'S')
		return ((t_vector){0, -0.66});
	if (c == 'E')
		return ((t_vector){-0.66, 0});
	return ((t_vector){0.66, 0});
}

static int	create_player(t_data *data, char pov, int i, int j)
{
	t_vector	position;
	t_player	player;

	if (data->player.pov != '0')
		return (error_mess(TOO_MANY_P), FAIL);
	player.pov = pov;
	position.x = j + 0.5;
	position.y = i + 0.5;
	player.pos = position;
	player.dir = set_dir(pov);
	player.plane = set_plane(pov);
	data->player = player;
	return (SUCCESS);
}

int	init_player(t_data *data, char **map)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	result = FAIL;
	while (map && map[i])
	{
		j = 0;
		while (map[i] && map[i][j])
		{
			if (is_pov(map[i][j]) == SUCCESS)
			{
				if (create_player(data, map[i][j], i, j) == FAIL)
					return (FAIL);
				map[i][j] = '0';
				result = SUCCESS;
			}
			j++;
		}
		i++;
	}
	if (result == FAIL)
		error_mess(NO_PLAYER);
	return (result);
}
