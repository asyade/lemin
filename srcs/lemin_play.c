/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lm_process_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:27:19 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/13 11:14:16 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	do_turn(t_map *map, t_room *rm, int depth, int c)
{
	if (rm->suit && rm->suit->lem != 0 && rm->suit != map->end)
		do_turn(map, rm->suit, depth + 1, c);
	ft_putchar('L');
	if (rm->suit == map->end && !(rm->lem == 0) && ++rm->suit->lem)
		ft_putnbr(rm->lem);
	else if (rm == map->start)
	{
		if (rm->lem <= 0)
			return ;
		if (rm->suit == map->end && ++rm->suit->lem)
			rm->lem--;
		else
			rm->suit->lem = map->count - --rm->lem;
		ft_putnbr(rm->suit->lem);
	}
	else
	{
		ft_putnbr(rm->lem);
		rm->suit->lem = (rm->suit) ? rm->lem : rm->suit->lem;
		rm->lem = 0;
	}
	(c) ? ft_printf("-\x1b[%dm%s\x1b[0m", rm->suit->color, rm->suit->name) : ft_printf("-%s", rm->suit->name);
	(depth != 0) ? ft_putchar(' ') : (NULL);
}

int			lm_is_direct(t_map *map)
{
	t_pipe	*pipe;
	t_list	*p;

	p = map->start->pipes;
	while (p)
	{
		pipe = (t_pipe *)p->content;
		if (pipe->a == map->end || pipe->b == map->end)
			return (1);
		p = p->next;
	}
	return (0);
}

void		lm_process_direct(t_map *map)
{
	int		i;

	i = 0;
	while (++i <= map->count)
		ft_printf("L%d-%s\n", i, map->end->name);
}

void		lm_process_path(t_map *map, int color)
{
	t_room	*curr;

	map->start->lem = map->count;
	if (lm_is_direct(map))
		return (lm_process_direct(map));
	curr = map->start;
	while (map->end->lem < map->count)
	{
		if (curr->lem == 0)
			curr = curr->suit;
		do_turn(map, curr, 0, color);
		ft_putchar('\n');
	}
}
