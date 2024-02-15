#ifndef CUB_H
# define CUB_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "mlx_linux/mlx.h"

# define BUFFER_SIZE	1024
# define FAIL			1
# define SUCCESS		0
# define WIDTH			960
# define HEIGHT			720
# define TEXT_SIZE		64

# define ARG_ERR		"1 argument required (*.cub file)"
# define END_MAP		"Map not the final element of the file"
# define MALLOC_ERR		"Malloc error"
# define NO_PLAYER		"One Player's POV required (N, S, E or W)"
# define TOO_MANY_P		"Too many Player's POV in the map, only one required"
# define DUPLICATE_DIR	"Duplicate information in the file (only 1 line per direction, NO, SO, EA, WE)"
# define DUPLICATE_FC	"Duplicate information in the file (only 2 line, 1 for floor and 1 for ceiling"
# define MAP_MISS		"There's no map in this file"
# define NO_MISS		"Northern texture is missing"
# define SO_MISS		"Southern texture is missing"
# define EA_MISS		"Eastern texture is missing"
# define WE_MISS		"Western texture is missing"
# define F_MISS			"Floor colors are missing"
# define C_MISS			"Ceiling color are missing"
# define INVALID_EXT	"Invalid File Extension"
# define INVALID_TEXT	"Invalid Texture Format"
# define INVALID_SPACES	"Invalid map not surrounded by 1 or invalid space(s)"
# define WRONG_CHAR		"Wrong character(s) present in the map"
# define EMPTY_LINE		"Empty line in map"
# define INVALID_DFS	"Invalid map (inaccessible area(s))"
# define MLX_INIT		"Init MLX failed"
# define MLX_WIN		"Window creation failed"
# define MLX_IMG		"Extract image from xpm file failed"



typedef struct s_vector{
	double	x;
	double	y;
}					t_vector;

typedef struct s_dir_path{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
}					t_dir_path;

typedef struct s_text{
	void	*img_p;
	char	*img_a;
	int		bpp;
	int		size_line;
	int		endian;
}					t_text;

typedef struct s_dir_text{
	t_text	n;
	t_text	s;
	t_text	e;
	t_text	w;
}					t_dir_text;

typedef struct s_skyfloor{
	char	**c;
	int		c_color;
	char	**f;
	int		f_color;
}					t_skyfloor;

typedef struct s_player{
	char		pov;
	t_vector	pos;
	t_vector	dir; // Direction du player selon pov ?
	t_vector	plane; // Camera plane
}					t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img_ptr;
	char		*img_data;
	char		**map;
	t_skyfloor	fc_tab;
	t_dir_path	dir_tab;
	t_dir_text	dir_text;
	t_player	player;
}					t_data;

typedef struct s_axe
{
	int	*dx;
	int	*dy;
}				t_axe;
 
typedef struct t_cordo{
	int	rows;
	int	cols;
}			t_sizemap;


char	**duplicate_map(t_data *data);
char	**ft_split(char *s, char *charset);

char	*ft_strcpy(char *buffer, char *tmp);
char	*ft_strdup_start(char const *s, int start, int end);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

int		check_all_elem(t_data *data);
int 	check_file_extension(char *file_name);
int		check_map(t_data *data);
int		check_space(t_data *data);
int		check_text(t_data *data, char **text);
int		count_line_file(int fd);
int		create_dir(t_data *data, char **text);
int		create_skyfloor(t_data *data, char **text);
int		extract_raw_data(char **content, int fd);
int		ft_dfs(int y, int x, char **map);
int		ft_isdigit(int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strlen(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		find_nl(char *buffer);
int		init_player(t_data *data, char **map);
int		init_text(t_data *data, char **text);
int		is_dir(char *str);
int		is_empty_line(char *line);
int		is_in_charset(char c);
int		is_pov(char c);
int		is_skyfloor(char *str);
int		is_space(char c);
int		is_text_line(char *line);
int		is_valid_color_format(char **tab);
int		is_valid_texture_direction(char **tab);
int		line_size(char **map);
int		parser(char *file, t_data *data);
int		split_text_map(char **content, t_data *data);
int		ft_tablen(char **tab);

void	clean(int fd, char **content, t_data *data);
void	display_map(char **map);
void	display_skyfloor_color(t_data *data);
void	display_text(t_data *data);
void	error_mess(char *mess);
void	free_all(char **result);
void	ft_bzero(void *s, size_t n);
void	game_setup(t_data *data);
void	init_data(t_data *data);

t_axe	ft_init_axe(void);

t_sizemap	ft_rows_cols_map(char **map);

#endif