#include "cub.h"

// int	check_numb_color(char *nptr)
// {
// 	char	**tab;
// 	int		i;
// 	int		n;
// 	int		j;

// 	i = 0;
// 	n = 0;
// 	j = 0;
// 	tab = ft_split(nptr, ",\n");
// 	if (!tab)
// 		return (FAIL);
// 	if (ft_tablen(tab) != 3)
// 		return (free_all(tab), FAIL);
// 	while (tab[j])
// 	{
// 		while (tab[j][i])
// 		{
// 			if (!ft_isdigit(tab[j][i]))
// 				return (free_all(tab), FAIL);
// 			n = n * 10 + (tab[j][i] - '0');
// 		i++;
// 		}
// 		if (n < 0 || n > 255)
// 			return (free_all(tab), FAIL);
// 	j++;
// 	i = 0;
// 	n = 0;
// 	}
// 	return (free_all(tab), SUCCESS);
// }
void	init_ivector(t_ivector *vector)
{
	vector->x = 0;
	vector->y = 0;
}

int	check_tab(char **tab)
{
	if (!tab)
		return (FAIL);
	if (ft_tablen(tab) != 3)
		return (free_all(tab), FAIL);
	return (SUCCESS);
}

int	check_numb_color(char *nptr)
{
	char		**tab;
	t_ivector	v;
	int			j;

	init_ivector(&v);
	j = 0;
	tab = ft_split(nptr, ",\n");
	if (check_tab(tab) == FAIL)
		return (FAIL);
	while (tab[j])
	{
		while (tab[j][v.x])
		{
			if (!ft_isdigit(tab[j][v.x]))
				return (free_all(tab), FAIL);
			v.y = v.y * 10 + (tab[j][v.x] - '0');
		v.x++;
		}
		if (v.y < 0 || v.y > 255)
			return (free_all(tab), FAIL);
		j++;
		init_ivector(&v);
	}
	return (free_all(tab), SUCCESS);
}

int	is_valid_color_format(char **tab)
{
	int	tab_len;

	tab_len = ft_tablen(tab);
	if (tab_len < 2 || is_skyfloor(tab[0]) == FAIL)
		return (error_mess(INVALID_TEXT), FAIL);
	if (check_numb_color(tab[1]) == FAIL)
		return (error_mess(INVALID_TEXT), FAIL);
	return (SUCCESS);
}
