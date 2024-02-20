SRCS	= main.c ft_strcpy.c ft_strjoin.c ft_strlen.c gnl.c utils_gnl.c utils_str.c utils_char.c ft_split.c clean_data.c extract_data_from_file.c split_data.c display_error.c init_data.c start_parsing.c create_text.c check_content.c debug.c check_file_extension.c ft_strcmp.c is_valid_texture_direction.c is_valid_color_format.c duplicate_map.c depthsearch.c utils_dfs.c check_space.c game.c event.c

OBJS	= ${SRCS:.c=.o}
%.o: %.c
	$(CC) ${CFLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@
CC	= cc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -g3
NAME	= cub3D

${NAME}: ${OBJS}
				${CC} ${CFLAGS} ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -lm -o ${NAME} 
all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re:		fclean all