#include "cub.h"

int	create_skyfloor(t_data *data, char **text)
{
	if (text[0][0] == 'F' && (!data->fc_tab.f))
	{
		data->fc_tab.f = ft_split(text[1], ",\t");
		if (!data->fc_tab.f)
			return (error_mess(MALLOC_ERR), FAIL);
		return (SUCCESS);
	}
	else if (text[0][0] == 'C' && (!data->fc_tab.c))
	{
		data->fc_tab.c = ft_split(text[1], ",\t");
		if (!data->fc_tab.c)
			return (error_mess(MALLOC_ERR), FAIL);
		return (SUCCESS);
	}
	return (error_mess(DUPLICATE_FC), FAIL);
}

static int	create_dir_next(t_data *data, char **text)
{
	if (text[0][0] == 'E' && (!data->dir_tab.ea))
	{
		data->dir_tab.ea = ft_strdup_start(text[1], 0, ft_strlen(text[1]));
		if (!data->dir_tab.ea)
			return (error_mess(MALLOC_ERR), FAIL);
		return (SUCCESS);
	}
	else if (text[0][0] == 'W' && (!data->dir_tab.we))
	{
		data->dir_tab.we = ft_strdup_start(text[1], 0, ft_strlen(text[1]));
		if (!data->dir_tab.we)
			return (error_mess(MALLOC_ERR), FAIL);
		return (SUCCESS);
	}
	return (error_mess(DUPLICATE_DIR), FAIL);
}

int	create_dir(t_data *data, char **text)
{
	if (text[0][0] == 'N' && (!data->dir_tab.no))
	{
		data->dir_tab.no = ft_strdup_start(text[1], 0, ft_strlen(text[1]));
		if (!data->dir_tab.no)
			return (error_mess(MALLOC_ERR), FAIL);
		return (SUCCESS);
	}
	else if (text[0][0] == 'S' && (!data->dir_tab.so))
	{
		data->dir_tab.so = ft_strdup_start(text[1], 0, ft_strlen(text[1]));
		if (!data->dir_tab.so)
			return (error_mess(MALLOC_ERR), FAIL);
		return (SUCCESS);
	}
	return (create_dir_next(data, text));
}
