/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:10:51 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:10:53 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_valid_space(t_data *data, int y, int x)
{
	int	x_max;
	int	x_max_plus;
	int	x_max_min;
	int	y_max;

	x_max = ft_strlen(data->map[y]);
	x_max_plus = ft_strlen(data->map[y + 1]);
	x_max_min = x_max;
	if (y - 1 >= 0)
		x_max_min = ft_strlen(data->map[y - 1]);
	y_max = ft_tablen(data->map);
	if ((x + 1) < x_max && data->map[y][x + 1] == '0')
		return (FAIL);
	if ((x - 1) >= 0 && data->map[y][x - 1] == '0')
		return (FAIL);
	if ((y + 1) < y_max && x < x_max_plus && data->map[y + 1][x] == '0')
		return (FAIL);
	if ((y - 1) >= 0 && x < x_max_min && data->map[y - 1][x] == '0')
		return (FAIL);
	return (SUCCESS);
}

int	check_space(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if ((is_space(data->map[y][x]) == SUCCESS) \
				&& is_valid_space(data, y, x) == FAIL)
				return (FAIL);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}
