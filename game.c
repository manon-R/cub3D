#include "cub.h"

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

int	rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

void	game_setup(t_data *data)
{
	int	bpp;
	int	size_line;
	int	endian;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (error_mess(MLX_INIT));
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!data->win)
		return (free(data->mlx), error_mess(MLX_WIN));
	if (init_dir_textures(data) == FAIL)
		return (free(data->mlx), error_mess(MLX_IMG));
	data->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, \
					&bpp, &size_line, &endian);
	raycasting(data);
	mlx_hook(data->win, 2, 1L << 0, key_event, data);
	mlx_hook(data->win, 17, 1L << 17, exit_hook, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img_data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
