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

void	init_raycast(t_raycast *ray, t_data *data, int x)
{
	ray->camera.x = 2 * x / (double) WIDTH - 1;
	ray->ray_dir.x = data->player.dir.x + data->player.plane.x * ray->camera.x;
	ray->ray_dir.y = data->player.dir.y + data->player.plane.y * ray->camera.x;
	ray->map_x = (int) data->player.pos.x;
	ray->map_y = (int) data->player.pos.y;
	ray->delta_dist.x = (ray->ray_dir.x == 0) ? 1e30 : fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = (ray->ray_dir.y == 0) ? 1e30 : fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
	ray->side = 0;
}

void	init_step_and_side(t_raycast *ray, t_data *data)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_x = -1;
		ray->side_dist.x = (data->player.pos.x - ray->map_x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist.x = (ray->map_x + 1.0 - data->player.pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_y = -1;
		ray->side_dist.y = (data->player.pos.y - ray->map_y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist.y = (ray->map_y + 1.0 - data->player.pos.y) * ray->delta_dist.y;
	}
}

int	raycasting(t_data *data)
{
	int			x;
	t_raycast	ray;

	x = 0;
	draw_background(data);
	while( x < WIDTH)
	{
		init_raycast(&ray, data, x);
		init_step_and_side(&ray, data);
///////////////////////////////////////perform DDA///////////////////////////////////////////
		while (ray.hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (ray.side_dist.x < ray.side_dist.y)
			{
				ray.side_dist.x += ray.delta_dist.x;
				ray.map_x += ray.step_x;
				ray.side = 0;
			}
			else
			{
				ray.side_dist.y += ray.delta_dist.y;
				ray.map_y += ray.step_y;
				ray.side = 1;
			}
			//Check if ray has hit a wall
			
			if (data->map[ray.map_y][ray.map_x] == '1') 
				ray.hit = 1; // Inverser X et Y?
		}
		// //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(ray.side == 0)
			ray.perpWallDist = (ray.side_dist.x - ray.delta_dist.x);
		else
			ray.perpWallDist = (ray.side_dist.y - ray.delta_dist.y);
		// //Calculate height of line to draw on screen
		int lineHeight = (int)(HEIGHT / ray.perpWallDist);
//////////////////////////////////////////////////////////////////////////////////////////
		 //calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (ray.side == 0) 
			wallX = data->player.pos.y + ray.perpWallDist * ray.ray_dir.y;
		else
			wallX = data->player.pos.x + ray.perpWallDist * ray.ray_dir.x;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)TEXT_SIZE);
		if(ray.side == 0 && ray.ray_dir.x > 0) 
			texX = TEXT_SIZE - texX - 1;
		if(ray.side == 1 && ray.ray_dir.y < 0) 
			texX = TEXT_SIZE - texX - 1;
		       // How much to increase the texture coordinate per screen pixel
		double step = 1.0 * TEXT_SIZE/ lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		int y = drawStart;
		t_text text;
		text = init_text_image(data, "./textures/wall.xpm");
		while (y < drawEnd)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (TEXT_SIZE - 1);
			texPos += step;
			int pixel =  ((TEXT_SIZE * texY + texX) * 4);
			char *dest = text.img_a + pixel;
			int color = *(int *)dest;
			//make color darker for y-sides
			if(ray.side == 1) 
				color = (color >> 1) & 8355711;
			put_pixel_color(data, x, y, color);
			y++;
		}
		x++;
	}
	return (0);
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
	mlx_hook(data->win, 17, 1L << 17, exit_hook, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	mlx_loop(data->mlx);
	mlx_destroy_image(data->mlx, data->img_data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}


/*
	// if (pov == '?')
	// 	return ;
	// char *text_addr;
	// init_text_image(data, &text_addr, "./textures/wall.xpm");
	// color = *(int *)text_addr;// +qqle chose pour avoir la couleur du bon pixel
*/