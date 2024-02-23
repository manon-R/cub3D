/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:12:30 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:12:31 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		init_data(&data);
		if (check_file_extension(argv[1]) == FAIL || \
			parser(argv[1], &data) == FAIL)
			return (FAIL);
		else if (game_setup(&data) == SUCCESS)
			launch_game(&data);
	}
	else
		error_mess(ARG_ERR);
}
