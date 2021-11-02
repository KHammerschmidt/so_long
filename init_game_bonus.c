/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 09:37:19 by khammers          #+#    #+#             */
/*   Updated: 2021/11/02 14:29:18 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Loops through 2D array and saves the position y and x for
each enemy by incrementing the index p. */
static void	ft_read_enemy_positions(t_struct *so_long)
{
	int	x;
	int	y;
	int	p;

	p = 0;
	while (p < so_long->game.counter_enemy)
	{
		y = 0;
		while (y < (so_long->game.map_height))
		{
			x = 0;
			while (x < (so_long->game.map_width))
			{
				if (so_long->game.map[y][x] == 'G')
				{
					so_long->game.e_pos_x[p] = x;
					so_long->game.e_pos_y[p] = y;
					p++;
				}
				x++;
			}
			y++;
		}
	}
}

/* Allocates memory space for int * of enemies depending on how many
enemies were counted in the map. */
static void	ft_e_memory_allocation(t_map *game)
{
	game->e_pos_x = ft_calloc(game->counter_enemy + 1, (sizeof(int)));
	game->e_pos_y = ft_calloc(game->counter_enemy + 1, (sizeof(int)));
	game->e_pos_x_last = ft_calloc(game->counter_enemy + 1, (sizeof(int)));
	game->e_pos_y_last = ft_calloc(game->counter_enemy + 1, (sizeof(int)));
}

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

/* Initialies all variables to start the game, saves the player's position,
allocates memory space for enemy pointer and saves the respective enemy
positions. */
void	ft_game_init(t_struct *so_long)
{
	so_long->vars.img_size = 64;
	so_long->vars.window_width = so_long->vars.img_size
		* so_long->game.map_width;
	so_long->vars.window_height = so_long->vars.img_size
		* so_long->game.map_height;
	so_long->vars.window_mid_width = (so_long->vars.window_width / 2);
	so_long->vars.window_mid_height = (so_long->vars.window_height / 2);
	so_long->player.number_of_moves = 0;
	so_long->player.still_playing = 0;
	so_long->player.enemy_flag = 0;
	so_long->game_solved = 0;
	so_long->game.enemy_moved = 0;
	ft_player_position(so_long);
	ft_e_memory_allocation(&so_long->game);
	ft_read_enemy_positions(so_long);
}
