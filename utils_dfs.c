/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dfs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 16:26:42 by hrandria          #+#    #+#             */
/*   Updated: 2024/02/12 13:20:07 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	*ft_tab_axe(int a, int b, int c, int d)
{
	int	*axe_x;

	axe_x = (int *)malloc(4 * sizeof(int));
	if (!axe_x)
		return (0);
	axe_x[0] = a;
	axe_x[1] = b;
	axe_x[2] = c;
	axe_x[3] = d;
	return (axe_x);
}

t_axe	ft_init_axe(void)
{
	t_axe	axes;

	axes.dx = ft_tab_axe(0, 1, 0, -1);
	axes.dy = ft_tab_axe(-1, 0, 1, 0);
	return (axes);
}

int	line_size(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(map[0]);
	while (map[i])
	{
		if (max < ft_strlen(map[i]))
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}
