/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:11:25 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:11:26 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	error_mess(char *mess)
{
	printf("ERROR\n");
	if (mess)
		printf("%s\n", mess);
}
