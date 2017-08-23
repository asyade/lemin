/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:56:12 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/13 13:20:10 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room		*get_dest(t_room *current, t_pipe *link)
{
	return (link->a == current) ? link->b : link->a;
}

t_room		*pf_get_min(t_room *room)
{
	t_list	*p;
	t_room	*d;
	t_room	*min;

	min = NULL;
	p = room->pipes;
	while (p)
	{
		d = get_dest(room, (t_pipe *)p->content);
		if (!(d->flags & D_PROCCESS) && (!min || d->weight < min->weight))
			min = d;
		p = p->next;
	}
	if (min)
		min->flags |= D_PROCCESS;
	return (min);
}

void		pf_explore(t_map *map, t_room *room)
{
	t_pipe	*p;
	t_list	*lst;
	t_room	*d;

	if (room == map->end)
		return ;
	lst = room->pipes;
	while (lst)
	{
		p = (t_pipe *)lst->content;
		lst = lst->next;
		d = get_dest(room, p);
		if (!(d->flags & D_VISITED) && (d->weight == -1 ||
d->weight > room->weight + p->dist))
		{
			d->flags |= D_VISITED;
			d->weight = room->weight + p->dist;
			d->ant = room;
		}
	}
	while ((d = pf_get_min(room)))
		pf_explore(map, d);
}

int			pf_check_path(t_room *start, t_room *end)
{
	if (!end)
		return (0);
	if (!end->ant)
		return (end == start);
	else
		end->ant->suit = end;
	return (pf_check_path(start, end ? end->ant : NULL));
}

int			pf_find_path(t_map *map)
{
	map->paths = NULL;
	while (1)
	{
		pf_clean_map(map);
		pf_explore(map, map->start);
		if (!pf_check_path(map->start, map->end))
			break ;
		ft_lstadd(&map->paths, pf_dump_path(map));
		break ;
	}
	if (!map->paths)
		return (0);
	return (1);
}