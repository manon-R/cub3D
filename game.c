#include "cub.h"

int	init_text(t_data *data, char **text)
{
	if (text[0][0] == 'F' || text[0][0] == 'C')
		return (create_skyfloor(data, text));
	else
		return (create_dir(data, text));
}

t_text	init_text_image(t_data *data, char *path)
{
	int		w;
	int		h;
	t_text	texture;

	texture.img_p = mlx_xpm_file_to_image(data->mlx, path, &w, &h);
	if (!texture.img_p)
		return (error_mess(MLX_IMG), texture);
	texture.img_a = mlx_get_data_addr(texture.img_p, \
					&(texture.bpp), &(texture.size_line), &(texture.endian));
	return (texture);
}

int	init_dir_textures(t_data *data)
{
	data->dir_text.n = init_text_image(data, data->dir_tab.no);
	if (!data->dir_text.n.img_p)
		return (FAIL);
	data->dir_text.s = init_text_image(data, data->dir_tab.so);
	if (!data->dir_text.s.img_p)
		return (FAIL);
	data->dir_text.e = init_text_image(data, data->dir_tab.ea);
	if (!data->dir_text.e.img_p)
		return (FAIL);
	data->dir_text.w = init_text_image(data, data->dir_tab.we);
	if (!data->dir_text.w.img_p)
		return (FAIL);
	return (SUCCESS);
}

void	launch_game(t_data *data)
{
	raycasting(data);
	mlx_hook(data->win, 2, 1L << 0, key_event, data);
	mlx_hook(data->win, 17, 1L << 17, exit_hook, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	mlx_loop(data->mlx);
	final_clean(data);
}

int	game_setup(t_data *data)
{
	int	bpp;
	int	size_line;
	int	endian;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (error_mess(MLX_INIT), FAIL);
	if (init_dir_textures(data) == FAIL)
		return (final_clean(data), FAIL);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (free(data->mlx), error_mess(MLX_WIN), FAIL);
	data->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img_ptr)
		return (final_clean(data), FAIL);
	data->img_data = mlx_get_data_addr(data->img_ptr, \
					&bpp, &size_line, &endian);
	return (SUCCESS);
}
