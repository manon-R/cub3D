#include "cub.h"

int	check_file_extension(char *file_name)
{
	int		len;
	char	*ext;

	len = ft_strlen(file_name);
	ext = ".cub";
	if (len < 5 || ft_strncmp(file_name + (len - 4), ext, 4) != 0)
		return (error_mess(INVALID_EXT), FAIL);
	return (SUCCESS);
}
