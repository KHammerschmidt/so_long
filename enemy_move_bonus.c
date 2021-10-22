/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:54:45 by khammers          #+#    #+#             */
/*   Updated: 2021/10/22 22:49:54 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Puts on the new enemy position a 'G' to rebuild the map accordingly. */
void	ft_update_map_enemy(t_map *game, int p, int t, int s)
{
	if (game->keycode_enemy[p] == KEY_D)
		game->map[t][s + 1] = 'G';
	if (game->keycode_enemy[p] == KEY_A)
		game->map[t][s - 1] = 'G';
	if (game->keycode_enemy[p] == KEY_S)
		game->map[t + 1][s] = 'G';
	if (game->keycode_enemy[p] == KEY_W)
		game->map[t - 1][s] = 'G';
}

/* Sets the position of the enemys based on their random move. Also saves
the last enemy position. */
void	ft_next_enemy_position(t_map *game, int p)
{
	int	t;
	int	s;

	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	game->map[t][s] = '0';
	game->e_pos_y_last[p] = game->e_pos_y[p];
	game->e_pos_x_last[p] = game->e_pos_x[p];
	if (game->keycode_enemy[p] == KEY_D)
		game->e_pos_x[p] = s + 1;
	if (game->keycode_enemy[p] == KEY_A)
		game->e_pos_x[p] = s - 1;
	if (game->keycode_enemy[p] == KEY_S)
		game->e_pos_y[p] = t + 1;
	if (game->keycode_enemy[p] == KEY_W)
		game->e_pos_y[p] = t - 1;
	ft_update_map_enemy(game, p, t, s);
}

/* Randomly generate the enemy's movement, with % 4 and assign 0-3 a
direction (north, south, west, east) and test if the enemy can go there. */
int	ft_generate_e_move(t_map *game, int p)
{
	int	nbr;
	int	move_indicator;

	nbr = rand();
	move_indicator = nbr % 4;
	if (move_indicator == 3)
		return (ft_check_e_move_east(game, p));
	if (move_indicator == 2)
		return (ft_check_e_move_south(game, p));
	if (move_indicator == 1)
		return (ft_check_e_move_north(game, p));
	if (move_indicator == 0)
		return (ft_check_e_move_west(game, p));
	return (0);
}

/* For each enemy a random movement is generated (max. 4 times
in case enemy cannot move). If it has been tried 4 times, keycode
is set to 99 to make the enenmy not move this time. If the move
is viable, the enemy's position is changed calling
ft_change_enemy_position(). */
void	ft_enemy_movement(t_map *game)
{
	int	p;
	int	flag;
	int	e_move;

	p = 0;
	while (p < game->counter_enemy)
	{
		flag = 0;
		e_move = 5;
		while (e_move != 0 && flag != 4)
		{
			e_move = ft_generate_e_move(game, p);
			flag++;
		}
		if (flag == 4)
			game->keycode_enemy[p] = 99;
		else
			ft_next_enemy_position(game, p);
		p++;
	}
}
