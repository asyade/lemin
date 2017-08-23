#include "lemin.h"

void	lemin_free(t_map **map)
{
    if (!*map)
        return ;
    if ((*map)->buffer)
        free((*map)->buffer);
    free(*map);
    *map = NULL;
}