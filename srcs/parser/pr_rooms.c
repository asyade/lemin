#include "lemin.h"

static int  rm_is_valid(char *buffer)
{
	char	*buf;

	buf = buffer;
	skip_blank(&buf);
	if (!ft_isalnum(*buf) || *buf == LEM_CHAR)
		return (0);
	skip_alnum(&buf);
	if (!skip_blank(&buf))
		return (0);
	if (!skip_num(&buf))
		return (0);
	if (!skip_blank(&buf))
		return (0);
	if (!skip_num(&buf))
		return (0);
	skip_blank(&buf);
	if (*buf != '\n')
		return (0);
	return (1);
}

static void	rm_get(char **buffer, t_map *map, int flag)
{
	t_room	*rm;
	char	*old;

	rm = ft_memalloc(sizeof(t_room));
	rm->flags = flag;
	old = *buffer;
	skip_alnum(&old);
	*old = '\0';
	rm->name = ft_strdup(*buffer);
	*old = ' ';
	*buffer = old;
	skip_blank(buffer);
	rm->x = ft_atoiinc(buffer);
	skip_blank(buffer);
	rm->y = ft_atoiinc(buffer);
	rm->color = ((rm->x * rm->y) % 7) + 31;
	if (!map->rooms)
		map->rooms = rm;
	else
	{
		rm->next = map->rooms;
		map->rooms = rm;
	}
}

int		parse_rooms(char **buffer, t_map *map)
{
	int	flag;

	map->rooms = NULL;
	if (**buffer == '\n')
		*buffer += 1;
	flag = 0;
    while (**buffer && (**buffer == COM_CHAR || rm_is_valid(*buffer)))
    {
		flag = (last_flag(*buffer, map->buffer)) ? last_flag(*buffer, map->buffer) : flag;
		if (is_comment(buffer))
			continue ;
		rm_get(buffer, map, flag);
		if (flag & FSTART)
			map->start = map->rooms;
		else if (flag & FEND)
			map->end = map->rooms;
		flag = 0;
		if (**buffer == '\n')
			*buffer += 1;
	}
    return (map->rooms ? 1 : 0);
}