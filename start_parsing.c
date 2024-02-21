#include "cub.h"

int	parser(char *file, t_data *data)
{
	int		fd;
	int		size;
	char	**content;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_mess(NULL), perror(file), FAIL);
	size = count_line_file(fd);
	close(fd);
	content = malloc((size + 1) * sizeof(char *));
	if (!content)
		return (error_mess(MALLOC_ERR), FAIL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error_mess(NULL), perror(file), free_all(content), FAIL);
	if (extract_raw_data(content, fd) == FAIL || !content)
		return (free_all(content), close(fd), FAIL);
	if (split_text_map(content, data) == FAIL || check_all_elem(data) == FAIL)
		return (free_all(content), close(fd), FAIL);
	if (init_player(data, data->map) == FAIL)
		return (clean(fd, content, data), FAIL);
	if (check_map(data) == FAIL)
		return (clean(fd, content, data), FAIL);
	return (free_all(content), SUCCESS);
}
