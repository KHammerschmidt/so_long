/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:16:37 by khammers          #+#    #+#             */
/*   Updated: 2021/10/21 10:58:13 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Printing the game instructions in the upper left corner of the window, onto
the wall in white colour. */
void	ft_game_instructions(t_struct *so_long)
{
	mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win, 10, 20,
		0xFFFFFFFF, GAME_INSTRUCTIONS_1);
	mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win, 10, 35,
		0xFFFFFFFF, GAME_INSTRUCTIONS_2);
}

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
	so_long.vars.mlx_win = mlx_new_window(so_long.vars.mlx, so_long.vars.window_width, so_long.vars.window_height, GAME_TITLE);
	ft_load_images(&so_long);
	ft_build_map(&so_long);
	mlx_hook(so_long.vars.mlx_win, 2, 0L, key_hook, &so_long);
	mlx_hook(so_long.vars.mlx_win, 17, 1L << 2, ft_close, &so_long);
	mlx_loop(so_long.vars.mlx);
	return (0);
}