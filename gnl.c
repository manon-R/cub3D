#include "cub.h"

static char	*ft_clean_buf(char *buffer)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (0);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	while (buffer[i])
		tmp[j++] = buffer[i++];
	tmp[j] = '\0';
	if (buffer[0])
		ft_bzero(buffer, ft_strlen(buffer));
	return (ft_strcpy(buffer, tmp));
}

static char	*ft_join_and_clean(char **result, char **buffer)
{
	char	*tmp;

	tmp = *result;
	*result = ft_strjoin(*result, *buffer);
	free(tmp);
	if (!*result)
		return (0);
	*buffer = ft_clean_buf(*buffer);
	if (!*buffer)
		return (free(*result), NULL);
	return (*result);
}

static char	*gnl_subpart(char **result, char **buffer, int read_size, int fd)
{
	if (!*buffer)
	{
		*buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!*buffer)
			return (0);
		(*buffer)[0] = '\0';
	}
	if (ft_strlen(*buffer) != 0)
	{
		*result = ft_join_and_clean(result, buffer);
		if (!*result)
			return (free(*result), NULL);
	}
	else
	{
		read_size = read(fd, *buffer, BUFFER_SIZE);
		if (read_size == -1 || read_size == 0)
			return (free(*buffer), *buffer = 0, NULL);
		(*buffer)[read_size] = '\0';
		*result = ft_join_and_clean(result, buffer);
		if (!*result)
			return (free(*result), NULL);
	}
	return (*result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE == 0)
		return (0);
	result = 0;
	read_size = 1;
	result = gnl_subpart(&result, &buffer, read_size, fd);
	if (!result)
		return (NULL);
	while (find_nl(result) == 0 && read_size)
	{
		read_size = read(fd, buffer, BUFFER_SIZE);
		if (read_size == -1)
			return (free(result), NULL);
		if (read_size == 0)
			return (result);
		buffer[read_size] = '\0';
		result = ft_join_and_clean(&result, &buffer);
		if (!result)
			return (NULL);
	}
	return (result);
}
