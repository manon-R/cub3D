/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depthsearch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:24:24 by hrandria          #+#    #+#             */
/*   Updated: 2024/02/22 15:03:51 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_sizemap	ft_rows_cols_map(char **map)
{
	t_sizemap	sizemap;

	sizemap.cols = ft_tablen(map);
	return (sizemap);
}

int	ft_is_valid(int px, int py, char **map)
{
	t_sizemap	sizemap;

	sizemap = ft_rows_cols_map(map);
	sizemap.rows = ft_strlen(map[py]);
	if (px < 0 || px >= sizemap.rows || py < 0 || py >= sizemap.cols)
		return (FAIL);
	if (map[py][px] && map[py][px] == '1')
		return (FAIL);
	return (SUCCESS);
}

int	ft_dfs(int y, int x, char **map)
{
	t_axe	axes;
	int		i;
	int		px;
	int		py;

	i = 0;
	axes = ft_init_axe();
	if (map && map[y][x] == '1')
		return (FAIL);
	map[y][x] = 'X';
	while (i < 4)
	{
		py = y + axes.dy[i];
		px = x + axes.dx[i];
		if (ft_is_valid(px, py, map) == 0 && map[py][px] != 'X')
		{
			if (ft_dfs(py, px, map) == 0)
				return (free(axes.dx), free(axes.dy), SUCCESS);
		}
		i++;
	}
	return (free(axes.dx), free(axes.dy), FAIL);
}
