/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:16:37 by khammers          #+#    #+#             */
/*   Updated: 2021/11/02 20:00:45 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Main function of the project 'so_long' calling functions from the graphical
library MiniLibX. */
int	main(int argc, char **argv)
{
	t_struct	so_long;

	if (ft_handle_input(argc, argv) == -1)
		exit(0);
	ft_map_init(&so_long);
	ft_define_map_size(argv[1], &so_long);
	if (ft_map_errors(&so_long) == -1)
		ft_close(&so_long);
	so_long.vars.mlx = mlx_init();
	ft_game_init(&so_long);
	ft_image_handling(&so_long);
	mlx_hook(so_long.vars.mlx_win, 2, 0L, key_hook, &so_long);
	mlx_hook(so_long.vars.mlx_win, 17, 1L << 2, ft_close, &so_long);
	mlx_loop(so_long.vars.mlx);
	return (0);
}
