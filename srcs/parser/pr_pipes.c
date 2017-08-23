#include "lemin.h"

static int  	pipe_is_valid(char *buffer)
{
	char	*buf;

	buf = buffer;
	skip_blank(&buf);
	if (!ft_isalnum(*buf) || *buf == LEM_CHAR)
		return (0);
	skip_alnum(&buf);
	if (*buf++ != SEP_CHAR)
		return (0);
	if (!ft_isalnum(*buf) || *buf == LEM_CHAR)
		return (0);
	skip_alnum(&buf);
	if (*buf != '\n')
	   return (0);
	return (1);
}

static t_room	*get_link(char *name, t_pipe *p, t_room *rm)
{
	while (rm)
	{
		if (ft_strequ(name, rm->name))
		{
			ft_lstadd(&rm->pipes, ft_lstcreate(p, sizeof(t_pipe)));
			return (rm);
		}
		rm = rm->next;
	}
	return (NULL);
}

static int		pipe_get(char **buffer, t_map *map)
{
	t_pipe	*p;
	char	*old;
	t_list	*l;

	p = ft_memalloc(sizeof(t_pipe));
	skip_blank(buffer);	
	old = ft_strchr(*buffer, '-');
	*old = '\0';
	if (!(p->a = get_link(*buffer, p, map->rooms)))
	{
		free(p);
		map->error |= ERR_INVPIPE;
		return (0);
	}
	*old = '-';
	*buffer = old + 1;
	old = ft_strchr(*buffer, '\n');
	*old = '\0';
	if (!(p->b = get_link(*buffer, p, map->rooms)))
	{
		l = p->a->pipes;
		map->error |= ERR_INVPIPE;		
		p->a->pipes = p->a->pipes->next;
		free(l);
		free(p);
		return (0);
	}
	*old = '\n';
	*buffer = old + 1;
	if (!map->pipes)
		map->pipes = p;
	else
	{
		p->next = map->pipes;
		map->pipes = p;
	}
	return (1);
}

int				parse_pipes(char **buffer, t_map *map)
{
	if (**buffer == '\n')
		*buffer += 1;
	while (**buffer && (**buffer == COM_CHAR || pipe_is_valid(*buffer)))
	{
		if (is_comment(buffer))
			continue ;
		if (!pipe_get(buffer, map))
		{
			map->error |= ERR_BADPIPE;
			return (0);
		}
		map->pipes->dist = pf_get_dist(map->pipes->a->x, map->pipes->a->y, map->pipes->b->x, map->pipes->b->y);		
		if (**buffer == '\n')
			*buffer += 1;
	}
	return (map->pipes ? 1 : 0);
}