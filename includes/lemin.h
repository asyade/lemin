#ifndef LEMIN_H
# define LEMIN_H

# include "ft_printf.h"
# include "libft.h"
# include "structs.h"

# define P_SILENT     0x001
# define P_COLOR      0x002
# define P_NODOUB     0x003

# define D_PROCCESS   0x200
# define D_VISITED    0x400

# define ERR_NOLEM	  0x001
# define ERR_NOROOM	  0x002
# define ERR_NOPIPE   0x004
# define ERR_BADPIPE  0x008
# define ERR_NOSTART  0x010
# define ERR_NOEND    0x020
# define ERR_TWOSTART 0x040
# define ERR_TWOEND   0x080
# define ERR_INVPIPE  0x200
# define ERR_RMDOUB   0x400

# define FSTART       0x020
# define FEND         0x010

# define COM_CHAR   '#'
# define SEP_CHAR	'-'
# define LEM_CHAR	'L'

# define CMD_START  "##start"
# define CMD_END    "##end"

/*
** Pass the ant one by one on the path found in map.paths, use recursion
*/

void	lm_process_path(t_map *map, int color);
void	lemin_free(t_map **map);

/*
** Fill a buffer using read(fd), stop at the first empty line or at \0
*/

char    *read_buffer(int fd);

/*
** Parsing utils
** Skip functions retrun 0 if first char is not space/alnum/digit
*/

int     last_flag(char *buffer, char *real_buffer);
int		is_comment(char **buffer);
int		pr_check(t_map *map);
int		skip_blank(char **buffer);
int		skip_num(char **buffer);
int     skip_alnum(char **buffer);

/*
** Parsing functions
** Returns NULL if the input data is insufficient,
** Does not display any output messages
** if specific error detected set trace in map.error
*/

int		parse_rooms(char **buffer, t_map *map);
int     parse_pipes(char **buffer, t_map *map);
t_map   *parse(char *buffer);

/*
**  Pathfindng
**  Simple dijkstra implementation
**  Set solved paths in map.paths
**  pf_find_path return 0 if no path found
*/

int		pf_get_dist(int x1, int y1, int x2, int y2);
void	pf_clean_map(t_map *map);
t_list	*pf_dump_path(t_map *map);
int		pf_find_path(t_map *map);

#endif