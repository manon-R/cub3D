#include "cub.h"

void	put_pixel_color(t_data *data, int x, int y, int color)
{
	char	*dest;
	int		pixel;

	pixel = (y * (WIDTH * 4)) + (x * 4);
	dest = data->img_data + pixel;
	*(int *)dest = color;
}
// return la couleur du pixel de la bonne texture selon la face du mur visible
 //A REVOIR POUR FORMULE qui boucle sur la texture en vertical
int	get_color(t_data *data, char pov)
{
	// int	pixel;
	// int	color;
	// char	*dest;

	// pixel = (y * (WIDTH * 4)) + (x * 4);
	if (data->player.pov == '?')
		return (FAIL);
	if (pov == 'N')
	// dest = data->dir_text.n.img_a
	// color = *(int *)dest + pixel;
		return (0x900C3F);
	if (pov == 'S')
		return (0x900C3F);
	if (pov == 'W')
		return (0x900C3F);
	if (pov == 'E')
		return (0x900C3F);
	return (0x900C3F);
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
	data->dir_text.n = init_text_image(data, data->dir_tab.so);
	if (!data->dir_text.s.img_p)
		return (FAIL);
	data->dir_text.n = init_text_image(data, data->dir_tab.ea);
	if (!data->dir_text.e.img_p)
		return (FAIL);
	data->dir_text.n = init_text_image(data, data->dir_tab.we);
	if (!data->dir_text.w.img_p)
		return (FAIL);
	return (SUCCESS);
}

int rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_wall(t_data *data, int lineHeight, int x, char pov)
{
	int		draw_start;
	int		draw_end;
	int		i;
	int		color;

	color = get_color(data, pov);
	// if (pov == '?')
	// 	return ;
	// char *text_addr;
	// init_text_image(data, &text_addr, "./textures/wall.xpm");
	// color = *(int *)text_addr;// +qqle chose pour avoir la couleur du bon pixel
	draw_start = (-lineHeight / 2) + (HEIGHT / 2);
	if (draw_start < 0)
		draw_start = 0;
	draw_end =  (lineHeight / 2) + (HEIGHT / 2);
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	i = draw_start;
	while (i < draw_end)
	{
		put_pixel_color(data, x, i, color);
		i++;
	}
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	data->fc_tab.c_color = 0xABCDEF;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel_color(data, x++, y, data->fc_tab.c_color);
		y++;
	}
	data->fc_tab.f_color = 0x977D76; //151, 125, 118 
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel_color(data, x++, y, data->fc_tab.f_color);
		y++;
	}
	draw_wall(data, 300, 0, 'N');
	draw_wall(data, 300, 1, 'N');
	draw_wall(data, 300, 2, 'N');
	draw_wall(data, 298, 3, 'N');
	draw_wall(data, 298, 4, 'N');
	draw_wall(data, 298, 5, 'N');
	draw_wall(data, 296, 6, 'N');
	draw_wall(data, 296, 7, 'N');
	draw_wall(data, 296, 8, 'N');
	draw_wall(data, 294, 9, 'N');
	draw_wall(data, 294, 10, 'N');
	draw_wall(data, 294, 11, 'N');
	draw_wall(data, 294, 12, 'N');
	draw_wall(data, 292, 13, 'N');
	draw_wall(data, 292, 14, 'N');
	draw_wall(data, 292, 15, 'N');
	draw_wall(data, 292, 16, 'N');
	draw_wall(data, 292, 17, 'N');
}

void	game_setup(t_data *data)
{
	int	bpp;
	int	size_line;
	int	endian;

	data->mlx = mlx_init();
	if (!data->mlx)
		return (error_mess(MLX_INIT));
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "First window");
	if (!data->win)
		return (free(data->mlx), error_mess(MLX_WIN));
	if (init_dir_textures(data) == FAIL)
		return (free(data->mlx), error_mess(MLX_IMG));
	data->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, \
					&bpp, &size_line, &endian);
	draw_background(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img_data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
