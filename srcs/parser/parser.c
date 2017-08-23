#include "lemin.h"

int    parse_lem_count(char **buffer, t_map *map)
{
	while (**buffer && is_comment(buffer))
		;
	skip_blank(buffer);
	if (!**buffer || !ft_isdigit(**buffer))
		return (0);
	map->count = ft_atoi(*buffer);
	skip_num(buffer);
	skip_blank(buffer);
	if (!**buffer || **buffer != '\n')
		return (0);
	return (1);
}

t_map   *parse(char *b)
{
	t_map   *map;
	char	*buffer;

	buffer = b;
	map = ft_memalloc(sizeof(t_map));
	map->buffer = buffer;
	if (!parse_lem_count(&buffer, map))
		map->error |= ERR_NOLEM;
	else if (!parse_rooms(&buffer, map))
		map->error |= ERR_NOROOM;
	else if (!parse_pipes(&buffer, map))
		map->error |= ERR_NOPIPE;
	map->error |= pr_check(map);
	return (map);
}