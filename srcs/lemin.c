#include "lemin.h"

static void		usage(void)
{
	ft_putendl("lemin: usage: lemin [-s || --silent] [-c || --color] < [map]");
	exit(1);
}

static void		print_error(int flag)
{
	ft_putendl("ERROR");
	if (flag & ERR_NOLEM)
		ft_printf("⇨    \x1b[31mNo ants\x1b[0m\n");
	if (flag & ERR_NOPIPE)
		ft_printf("⇨    \x1b[31mNo pipes\x1b[0m\n");
	if (flag & ERR_NOROOM)
		ft_printf("⇨    \x1b[31mNo rooms\x1b[0m\n");
	if (flag & ERR_NOEND)
		ft_printf("⇨    \x1b[31mNo start\x1b[0m\n");
	if (flag & ERR_NOSTART)
		ft_printf("⇨    \x1b[31mNo end\x1b[0m\n");
	if (flag & ERR_TWOEND)
		ft_printf("⇨    \x1b[31mMultiple end\x1b[0m\n");
	if (flag & ERR_TWOSTART)
		ft_printf("⇨    \x1b[31mMultiple start\x1b[0m\n");
	if (flag & ERR_INVPIPE)
		ft_printf("⇨    \x1b[31mInvalide pipes\x1b[0m\n");
}

static int   parse_av(int ac, char **av)
{
	int		ret;

	ret = 0;
	while (ac--)
	{
		if (ft_strequ(av[ac], "--silent") || ft_strequ(av[ac], "-s"))
			ret |= P_SILENT;
		else if (ft_strequ(av[ac], "--color") || ft_strequ(av[ac], "-c"))
			ret |= P_COLOR;
		else
			usage();
	}
	return (ret);
}

int     main(int ac, char **av)
{
	int		opts;
	t_map   *map;

	opts = parse_av(ac - 1, av + 1);
	if (!(map = parse(read_buffer(0))))
	{
		ft_printf("ERROR\n⇨    \x1b[31mUnable to parse map\x1b[0m\n");
		return (0);
	}
	if (map->error)
	{
		print_error(map->error);
		return (0);
	}
	map->opts = opts;
	if (!pf_find_path(map))
		ft_printf("ERROR\n⇨    \x1b[31mNo path found\x1b[0m\n");
	else
	{
		(!(opts & P_SILENT)) ? ft_putendl(map->buffer) : NULL;
		lm_process_path(map, opts & P_COLOR);		
	}
	lemin_free(&map);
	return (1);
}