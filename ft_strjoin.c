#include "cub.h"

static int	ft_compute_size(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;
	int		size;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (0);
	size = ft_compute_size(s2);
	if (s1)
		size += ft_strlen(s1);
	new_str = malloc((size + 1) * sizeof(char));
	if (!new_str)
		return (0);
	while (s1 && *s1)
		new_str[i++] = *(s1++);
	while (s2[j] && (s2[j] != '\n'))
		new_str[i++] = s2[j++];
	if (s2[j] && s2[j] == '\n')
		new_str[i++] = '\n';
	new_str[i] = '\0';
	return (new_str);
}
