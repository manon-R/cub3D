/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data_from_file.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:11:55 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:11:56 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	count_line_file(int fd)
{
	char	*result;
	int		size;
	char	c;

	size = 0;
	c = '0';
	result = get_next_line(fd);
	if (!result)
		return (0);
	size++;
	while (result)
	{
		if (is_empty_line(result) == FAIL || c == 'm')
		{
			size++;
			if (is_text_line(result) == FAIL)
				c = 'm';
		}
		free(result);
		result = get_next_line(fd);
	}
	free(result);
	return (size);
}

int	extract_raw_data(char **content, int fd)
{
	char	*result;
	int		i;
	char	c;

	i = 0;
	c = '0';
	result = get_next_line(fd);
	if (!result)
		return (FAIL);
	while (result)
	{
		if (is_empty_line(result) == FAIL || c == 'm')
		{
			if (is_text_line(result) == FAIL)
				c = 'm';
			content[i++] = ft_strdup_start(result, 0, ft_strlen(result));
			if (!content[i - 1])
				return (free_all(content), free(result), FAIL);
		}
		free(result);
		result = get_next_line(fd);
	}
	content[i++] = 0;
	return (free(result), SUCCESS);
}
