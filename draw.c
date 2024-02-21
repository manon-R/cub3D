#include "cub.h"

void	put_pixel_color(t_data *data, int x, int y, int color)
{
	char	*dest;
	int		pixel;

	pixel = (y * (WIDTH * 4)) + (x * 4);
	dest = data->img_data + pixel;
	*(int *)dest = color;
}

static t_text	get_text(t_raycast ray, t_data data)
{
	if (ray.side == 0)
	{
		if (ray.ray_dir.x < 0)
			return (data.dir_text.w);
		return (data.dir_text.e);
	}
	if (ray.ray_dir.y > 0)
		return (data.dir_text.s);
	return (data.dir_text.n);
}

void	draw_wall(t_data *data, t_draw_data *draw, int x, t_raycast *ray)
{
	int		y;
	int		pixel;
	int		color;
	t_text	text;
	char	*dest;

	y = draw->draw_se.x;
	while (y < draw->draw_se.y)
	{
		draw->tex.y = (int)draw->tex_pos & (TEXT_SIZE - 1);
		draw->tex_pos += draw->step;
		pixel = ((TEXT_SIZE * draw->tex.y + draw->tex.x) * 4);
		text = get_text(*ray, *data);
		dest = text.img_a + pixel;
		color = *(int *)dest;
		put_pixel_color(data, x, y, color);
		y++;
	}
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel_color(data, x++, y, data->fc_tab.c_color);
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
			put_pixel_color(data, x++, y, data->fc_tab.f_color);
		y++;
	}
}
