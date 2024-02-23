/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 16:12:03 by mle-bras          #+#    #+#             */
/*   Updated: 2024/02/23 16:12:04 by mle-bras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (charset[i] == c)
			return (SUCCESS);
		i++;
	}
	return (FAIL);
}

static int	ft_compute_size(char const *s, char *charset)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (in_charset(*s, charset) == SUCCESS)
			s++;
		if (*s && in_charset(*s, charset) == FAIL)
		{
			size++;
			while (*s && in_charset(*s, charset) == FAIL)
				s++;
		}
	}
	return (size);
}

char	*ft_strdup_start(char const *s, int start, int end)
{
	char	*dest;
	int		size;
	int		i;

	size = end - start;
	dest = malloc((size + 1) * sizeof(char));
	if (!dest)
		return (0);
	i = 0;
	while (start < end)
		dest[i++] = s[start++];
	dest[i] = '\0';
	return (dest);
}

static char	**ft_split_annexe(char *s, char **result, char *charset)
{
	int	start;
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (s[i])
	{
		while (in_charset(s[i], charset) == SUCCESS)
			i++;
		if (s[i] && in_charset(s[i], charset) == FAIL)
		{
			start = i;
			while (s[i] && in_charset(s[i], charset) == FAIL)
					i++;
			result[index] = ft_strdup_start(s, start, i);
			if (!result[index])
				return (free_all(result), NULL);
			index++;
		}
	}
	result[index] = 0;
	return (result);
}

char	**ft_split(char *s, char *charset)
{
	char	**result;

	result = malloc((ft_compute_size(s, charset) + 1) * sizeof(char *));
	if (!result)
		return (0);
	ft_split_annexe(s, result, charset);
	return (result);
}
