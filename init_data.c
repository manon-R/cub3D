#include "cub.h"

void	init_data(t_data *data)
{
	data->map = NULL;
	data->dir_tab.no = NULL;
	data->dir_tab.so = NULL;
	data->dir_tab.ea = NULL;
	data->dir_tab.we = NULL;
	data->fc_tab.f = NULL;
	data->fc_tab.f_color = 0x0;
	data->fc_tab.c = NULL;
	data->fc_tab.c_color = 0x0;
	data->player.pov = '0';
}

int	init_text(t_data *data, char **text)
{
	if (text[0][0] == 'F' || text[0][0] == 'C')
		return (create_skyfloor(data, text));
	else
		return (create_dir(data, text));
}

t_vector	set_dir(char c)
{
	if (c == 'N')
		return ((t_vector) {1, 0});
	if (c == 'S')
		return ((t_vector) {-1, 0});
	if (c == 'E')
		return ((t_vector) {0, 1});
	return ((t_vector) {0, -1});
}

static int	create_player(t_data *data, char pov, int i, int j)
{
	t_vector	position;
	t_vector	plane;
	t_player	player;

	if (data->player.pov != '0')
		return (error_mess(TOO_MANY_P), FAIL);
	player.pov = pov;
	position.x = j;
	position.y = i;
	plane.x = 0;
	plane.y = 0.66;
	player.pos = position;
	player.plane = plane;
	player.dir = set_dir(pov);
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
