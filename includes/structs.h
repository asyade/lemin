/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acorbeau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 13:27:07 by acorbeau          #+#    #+#             */
/*   Updated: 2017/08/13 13:27:08 by acorbeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct		s_room
{
	int				x;
	int				y;
	int				weight;
	char			*name;
	int				flags;
	int				lem;
	int				color;
	t_list			*pipes;
	struct s_room	*ant;
	struct s_room	*suit;	
	struct s_room	*next;
}					t_room;

typedef struct		s_pipe
{
	t_room			*a;
	t_room			*b;
	int				dist;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_map
{
	int				count;
	t_list			*paths;
	t_room			*rooms;
	t_room			*start;
	t_room			*end;
	t_pipe			*pipes;
	char			*buffer;
	int				error;
	int				opts;
}					t_map;

typedef struct		s_path
{
	t_room			*room;
	struct s_path	*next;
}					t_path;

#endif
