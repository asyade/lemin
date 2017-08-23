#include "lemin.h"


int     pr_check_limits(t_map *map)
{
	t_room	*rm;
	int		flags;
	int		ret;

	ret = 0;
	flags = 0;
	rm = map->rooms;
	while (rm)
	{
		if (rm->flags & FSTART && flags & FSTART)
			ret |= ERR_TWOSTART;
		else if (rm->flags & FSTART)
			flags |= FSTART;
		if (rm->flags & FEND && flags & FEND)
			ret |= ERR_TWOEND;
		else if (rm->flags & FEND)
			flags |= FEND;
		rm = rm->next;
	}
	if (!(flags & FSTART))
		ret |= ERR_NOSTART;
	if (!(flags & FEND))
		ret |= ERR_NOEND;
	return (ret);
}

int		pr_check(t_map *map)
{
	int		ret;

	ret = 0;
	ret |= pr_check_limits(map);
	if (map->count <= 0)
		ret |= ERR_NOLEM;
	if (!map->pipes)
		ret |= ERR_NOPIPE;
	return (ret);
}