#include "cub.h"

void	ft_destroy_img(t_data *data)
{
	c_texture(data);
	if (data->dir_text.e.img_p)
		mlx_destroy_image(data->mlx, data->dir_text.e.img_p);
	if (data->dir_text.n.img_p)
		mlx_destroy_image(data->mlx, data->dir_text.n.img_p);
	if (data->dir_text.s.img_p)
		mlx_destroy_image(data->mlx, data->dir_text.s.img_p);
	if (data->dir_text.w.img_p)
		mlx_destroy_image(data->mlx, data->dir_text.w.img_p);
	if (data->img_ptr)
		mlx_destroy_image(data->mlx, data->img_ptr);
}


int	exit_hook(t_data *data)
{
	ft_destroy_img(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(SUCCESS);
}

static void	key_cam(int keycode, t_data *data)
{
	double	old_dirx;
	double	old_planex;
	double	speed;

	old_dirx = data->player.dir.x;
	old_planex = data->player.plane.x;
	speed = ROT_SPEED;
	if (keycode == XK_LEFT)
		speed *= -1;
	data->player.dir.x = data->player.dir.x * cos(speed) - \
						data->player.dir.y * sin(speed);
	data->player.dir.y = old_dirx * sin(speed) + \
						data->player.dir.y * cos(speed);
	data->player.plane.x = data->player.plane.x * cos(speed) - \
							data->player.plane.y * sin(speed);
	data->player.plane.y = old_planex * sin(speed) + \
							data->player.plane.y * cos(speed);
}

static void	key_rl(int keycode, t_data *data)
{
	if (keycode == XK_A)
	{
		if (data->map[(int)data->player.pos.y][(int)(data->player.pos.x + \
			data->player.dir.y * MOVE_SPEED)] != '1')
			data->player.pos.x += data->player.dir.y * MOVE_SPEED;
		if (data->map[(int)(data->player.pos.y - data->player.dir.x * \
			MOVE_SPEED)][(int)data->player.pos.x] != '1')
			data->player.pos.y -= data->player.dir.x * MOVE_SPEED;
	}
	if (keycode == XK_D)
	{
		if (data->map[(int)data->player.pos.y][(int)(data->player.pos.x - \
			data->player.dir.y * MOVE_SPEED)] != '1')
			data->player.pos.x -= data->player.dir.y * MOVE_SPEED;
		if (data->map[(int)(data->player.pos.y + data->player.dir.x * \
			MOVE_SPEED)][(int)data->player.pos.x] != '1')
			data->player.pos.y += data->player.dir.x * MOVE_SPEED;
	}
}

static void	key_updown(int keycode, t_data *data)
{
	if (keycode == XK_W || keycode == XK_UP)
	{
		if (data->map[(int)data->player.pos.y][(int)(data->player.pos.x + \
			data->player.dir.x * MOVE_SPEED)] != '1')
			data->player.pos.x += data->player.dir.x * MOVE_SPEED;
		if (data->map[(int)(data->player.pos.y + data->player.dir.y * \
			MOVE_SPEED)][(int)data->player.pos.x] != '1')
			data->player.pos.y += data->player.dir.y * MOVE_SPEED;
	}
	if (keycode == XK_S || keycode == XK_DOWN)
	{
		if (data->map[(int)data->player.pos.y][(int)(data->player.pos.x - \
			data->player.dir.x * MOVE_SPEED)] != '1')
			data->player.pos.x -= data->player.dir.x * MOVE_SPEED;
		if (data->map[(int)(data->player.pos.y - data->player.dir.y * \
			MOVE_SPEED)][(int)data->player.pos.x] != '1')
			data->player.pos.y -= data->player.dir.y * MOVE_SPEED;
	}
}

int	key_event(int keycode, t_data *data)
{
	if (keycode == XK_ESCAPE)
		return (exit_hook(data), 0);
	if (keycode == XK_LEFT || keycode == XK_RIGHT)
		key_cam(keycode, data);
	if (keycode == XK_W || keycode == XK_UP || \
		keycode == XK_S || keycode == XK_DOWN)
		key_updown(keycode, data);
	if (keycode == XK_A || keycode == XK_D)
		key_rl(keycode, data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (SUCCESS);
}
