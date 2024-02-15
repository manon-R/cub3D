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
		else
			game_setup(&data);
	}
	else
		error_mess(ARG_ERR);
}
