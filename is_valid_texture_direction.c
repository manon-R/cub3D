#include "cub.h"

int	is_valid_texture_direction(char **tab)
{
	int	tab_len;

	tab_len = ft_tablen(tab);
	if (tab_len < 2 || is_dir(tab[0]) == FAIL || \
	ft_strlen(tab[1]) <= 2 || (tab[1][0] != '.' || tab[1][1] != '/'))
		return (error_mess(INVALID_TEXT), FAIL);
	return (SUCCESS);
}
