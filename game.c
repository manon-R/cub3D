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
int	get_color(t_data *data)
{
	// int	pixel;
	// int	color;
	// char	*dest;

	// pixel = (y * (WIDTH * 4)) + (x * 4);
	if (data->player.pov == '?')
		return (FAIL);
	// if (pov == 'N')
	// // dest = data->dir_text.n.img_a
	// // color = *(int *)dest + pixel;
	// 	return (0x900C3F);
	// if (pov == 'S')
	// 	return (0x900C3F);
	// if (pov == 'W')
	// 	return (0x900C3F);
	// if (pov == 'E')
	// 	return (0x900C3F);
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

void	draw_wall(t_data *data, int lineHeight, int x, int side)
{
	int		draw_start;
	int		draw_end;
	int		i;
	int		color;

	color = get_color(data);
	if (side == 1)
		color /= 2;
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
}

int	raycasting(t_data *data)
{
	int	x;

	x = 0;
	draw_background(data);
	while( x < WIDTH)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double) WIDTH - 1; //x-coordinate in camera space
		double rayDirX = data->player.dir.x + data->player.plane.x * cameraX;
		double rayDirY = data->player.dir.y + data->player.plane.y * cameraX;

		//which box of the map we're in
		int mapX = (int) data->player.pos.x;
		int mapY = (int) data->player.pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int	stepX;
		int	stepY;

		int hit = 0; //was there a wall hit?
		int side = 0; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->player.pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->player.pos.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->player.pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->player.pos.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			
			if (data->map[mapY][mapX] == '1') 
				hit = 1; // Inverser X et Y?
		}
		// //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		// //Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / perpWallDist);
		draw_wall(data, lineHeight, x, side);
		x++;
	}
	return (0);
}

int	key_event(int keycode, t_data *data)
{
    double moveSpeed = 0.2; //// const a definir
    double rotSpeed = 0.05; // const a definir
	// if (keycode == XK_ESCAPE)
	// 	return (exit_hook(vars), 0);
	if (keycode == XK_LEFT)
	{
		//both camera direction and camera plane must be rotated
      double oldDirX = data->player.dir.x;
      data->player.dir.x = data->player.dir.x * cos(-rotSpeed) - data->player.dir.y * sin(-rotSpeed);
      data->player.dir.y = oldDirX * sin(-rotSpeed) + data->player.dir.y * cos(-rotSpeed);
      double oldPlaneX = data->player.plane.x;
      data->player.plane.x = data->player.plane.x * cos(-rotSpeed) - data->player.plane.y * sin(-rotSpeed);
      data->player.plane.y = oldPlaneX * sin(-rotSpeed) + data->player.plane.y * cos(-rotSpeed);
	}
	if (keycode == XK_RIGHT)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->player.dir.x;
		data->player.dir.x = data->player.dir.x * cos(rotSpeed) - data->player.dir.y * sin(rotSpeed);
		data->player.dir.y = oldDirX * sin(rotSpeed) + data->player.dir.y * cos(rotSpeed);
		double oldPlaneX = data->player.plane.x;
		data->player.plane.x = data->player.plane.x * cos(rotSpeed) - data->player.plane.y * sin(rotSpeed);
		data->player.plane.y = oldPlaneX * sin(rotSpeed) + data->player.plane.y * cos(rotSpeed);
	}
	if (keycode == XK_UP)
	{
		if(data->map[(int)data->player.pos.y][(int)(data->player.pos.x + data->player.dir.x * moveSpeed)] != '1')
			data->player.pos.x += data->player.dir.x * moveSpeed;
		if(data->map[(int)(data->player.pos.y + data->player.dir.y * moveSpeed)][(int)data->player.pos.x] != '1')
			data->player.pos.y += data->player.dir.y * moveSpeed;
	}
	if (keycode == XK_DOWN)
	{
		if(data->map[(int)data->player.pos.y][(int)(data->player.pos.x - data->player.dir.x * moveSpeed)] != '1')
			data->player.pos.x -= data->player.dir.x * moveSpeed;
		if(data->map[(int)(data->player.pos.y - data->player.dir.y * moveSpeed)][(int)data->player.pos.x] != '1')
			data->player.pos.y -= data->player.dir.y * moveSpeed;
	}
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (SUCCESS);
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
	// if (init_dir_textures(data) == FAIL)
	// 	return (free(data->mlx), error_mess(MLX_IMG));
	data->img_ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img_data = mlx_get_data_addr(data->img_ptr, \
					&bpp, &size_line, &endian);
	raycasting(data);
	mlx_hook(data->win, 2, 1L << 0, key_event, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img_data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
