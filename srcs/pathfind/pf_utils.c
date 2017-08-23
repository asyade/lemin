/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:49:26 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/13 11:50:07 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list	*pf_dump_path(t_map *map)
{
	t_list		*path;
	t_room		*rm;

	path = NULL;
	rm = map->end;
	while (rm)
	{
		ft_lstadd(&path, ft_lstcreate(rm, sizeof(t_room)));
		rm = rm->ant;
	}
	return (path);
}

void	pf_clean_map(t_map *map)
{
	t_room *rm;
	rm = map->rooms;
	while (rm)
	{
		rm->weight = (rm->flags & FSTART) ? 0 : -1;
		rm->ant = NULL;
		rm->suit = NULL;
		rm->flags &= ~(D_VISITED | D_PROCCESS);
		rm = rm->next;
	}
}

int		pf_get_dist(int x1, int y1, int x2, int y2)
{
	int distancex;
	int distancey;
	int	distance;

	distancex = (x2 - x1) * (x2 - x1);
	distancey = (y2 - y1) * (y2 - y1);
	distance = distancex + distancey;
	return ((int)distance);
}
