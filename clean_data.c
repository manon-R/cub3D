/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:13:54 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:13:55 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	free_all(char **result)
{
	int	i;

	i = 0;
	while (result && result[i])
	{
		free(result[i]);
		result[i] = NULL;
		i++;
	}
	if (result)
	{
		free(result);
		result = NULL;
	}
}

void	clean(int fd, char **content, t_data *data)
{
	if (content)
		free_all(content);
	if (data->map)
	{
		free_all(data->map);
		data->map = NULL;
	}
	close(fd);
}

void	final_clean(t_data *data)
{
	ft_destroy_img(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(SUCCESS);
}
