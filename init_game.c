/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:37:19 by khammers          #+#    #+#             */
/*   Updated: 2021/10/26 12:01:59 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Loops through 2D array to detect the position of player (x & y). */
void	ft_player_position(t_struct *so_long)
{
	int	x;
	int	y;

	so_long->player.player_position_last_y = so_long->player.player_position_y;
	so_long->player.player_position_last_x = so_long->player.player_position_x;
	y = 0;
	while (y < (so_long->game.map_height))
	{
		x = 0;
		while (x < (so_long->game.map_width))
		{
			if (so_long->game.map[y][x] == 'P')
			{
				so_long->player.player_position_y = y;
				so_long->player.player_position_x = x;
			}
			x++;
		}
		y++;
	}
}

/* Initialies all variables to start the game, saves the player's position. */
void	ft_game_init(t_struct *so_long)
{
	int	p;

	p = 0;
	so_long->vars.img_size = 64;
	so_long->vars.window_width = so_long->vars.img_size
		* so_long->game.map_width;
	so_long->vars.window_height = so_long->vars.img_size
		* so_long->game.map_height;
	so_long->vars.window_mid_width = (so_long->vars.window_width / 2);
	so_long->vars.window_mid_height = (so_long->vars.window_height / 2);
	so_long->player.number_of_moves = 0;
	so_long->player.still_playing = 0;
	ft_player_position(so_long);
}
