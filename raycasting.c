#include "cub.h"

static void	init_raycast(t_raycast *ray, t_data *data, int x)
{
	ray->camera.x = 2 * x / (double) WIDTH - 1;
	ray->ray_dir.x = data->player.dir.x + data->player.plane.x * ray->camera.x;
	ray->ray_dir.y = data->player.dir.y + data->player.plane.y * ray->camera.x;
	ray->map.x = (int) data->player.pos.x;
	ray->map.y = (int) data->player.pos.y;
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = 1e30;
	else
		ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	if ((ray->ray_dir.y == 0))
		ray->delta_dist.y = 1e30;
	else
		ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
	ray->hit = 0;
	ray->side = 0;
}

static void	init_step_and_side(t_raycast *ray, t_data *data)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (data->player.pos.x - ray->map.x) * \
							ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map.x + 1.0 - data->player.pos.x) * \
							ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (data->player.pos.y - ray->map.y) * \
							ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map.y + 1.0 - data->player.pos.y) * \
						ray->delta_dist.y;
	}
}

static void	perform_dda(t_raycast *ray, t_data *data)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map.y += ray->step.y;
			ray->side = 1;
		}
		if (data->map[ray->map.y][ray->map.x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wallDist = (ray->side_dist.x - ray->delta_dist.x);
	else
		ray->perp_wallDist = (ray->side_dist.y - ray->delta_dist.y);
	ray->line_height = (int)(HEIGHT / ray->perp_wallDist);
}

static void	init_draw_data(t_draw_data *draw, t_data *data, t_raycast ray)
{
	draw->draw_se.x = -ray.line_height / 2 + HEIGHT / 2;
	if (draw->draw_se.x < 0)
		draw->draw_se.x = 0;
	draw->draw_se.y = ray.line_height / 2 + HEIGHT / 2;
	if (draw->draw_se.y >= HEIGHT)
		draw->draw_se.y = HEIGHT - 1;
	if (ray.side == 0)
		draw->wall_x = data->player.pos.y + ray.perp_wallDist * ray.ray_dir.y;
	else
		draw->wall_x = data->player.pos.x + ray.perp_wallDist * ray.ray_dir.x;
	draw->wall_x -= floor((draw->wall_x));
	draw->tex.x = (int)(draw->wall_x * (double)TEXT_SIZE);
	if (ray.side == 0 && ray.ray_dir.x > 0)
		draw->tex.x = TEXT_SIZE - draw->tex.x - 1;
	if (ray.side == 1 && ray.ray_dir.y < 0)
		draw->tex.x = TEXT_SIZE - draw->tex.x - 1;
	draw->step = 1.0 * TEXT_SIZE / ray.line_height;
	draw->tex_pos = (draw->draw_se.x - HEIGHT / 2 + ray.line_height / 2) * \
					draw->step;
}

int	raycasting(t_data *data)
{
	int			x;
	t_raycast	ray;
	t_draw_data	draw;

	x = 0;
	draw_background(data);
	while (x < WIDTH)
	{
		init_raycast(&ray, data, x);
		init_step_and_side(&ray, data);
		perform_dda(&ray, data);
		init_draw_data(&draw, data, ray);
		draw_wall(data, &draw, x, &ray);
		x++;
	}
	return (0);
}
