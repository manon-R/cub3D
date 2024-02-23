/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:11:18 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:11:19 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	display_map(char **map)
{
	int	i;

	i = 0;
	while (map && map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

void	display_text(t_data *data)
{
	printf("************ DIR TAB ************\n");
	if (data->dir_tab.no)
		printf("NO texture = %s\n", data->dir_tab.no);
	if (data->dir_tab.so)
		printf("SO texture = %s\n", data->dir_tab.so);
	if (data->dir_tab.ea)
		printf("EA texture = %s\n", data->dir_tab.ea);
	if (data->dir_tab.we)
		printf("WE texture = %s\n", data->dir_tab.we);
}

void	display_skyfloor_color(t_data *data)
{
	int	i;

	i = 0;
	printf("************ FLOOR / CEILING COLOR ************\n");
	if (data->fc_tab.f)
	{
		while (data->fc_tab.f[i])
		{
			printf("Floor color[%i] = %s\n", i, data->fc_tab.f[i]);
			i++;
		}
	}
	i = 0;
	if (data->fc_tab.c)
	{
		while (data->fc_tab.c[i])
		{
			printf("Ceiling color[%i] = %s\n", i, data->fc_tab.c[i]);
			i++;
		}
	}
}
