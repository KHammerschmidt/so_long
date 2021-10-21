/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:54:45 by khammers          #+#    #+#             */
/*   Updated: 2021/10/21 17:21:04 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <stdio.h>

void	ft_support_enemy_move(t_map *game)
{
	int t;
	int s;
	int	p;

	p = 0;
	while (p < game->counter_enemy)
	{
		int	t;
		int	s;

		t = game->e_pos_y_next[p];
		s = game->e_pos_x_next[p]
		game->map[t][s] = '0';

		game->e_pos_y[p] = game->e_pos_y_last[p];
		game->e_pos_x[p] = game->e_pos_x_last[p];

		t = game->e_pos_y[p];
		s = game->e_pos_x[p]
		game->map[t][s] = 'G';
		p++;
	}

}

/* Functions changes the enemy's position, depending on the randomly generated
keycode. The last position of the enemy is saved to test if the player moves
into an enemy. */
void	ft_move_enemy_back(t_map *game)
{
	int t;
	int s;
	int	p;

	p = 0;
	while (p < game->counter_enemy)
	{
		game->e_pos_y[p] = game->e_pos_y_last[p];
		game->e_pos_x[p] = game->e_pos_x_last[p];


		t = game->e_pos_y[p];
		s = game->e_pos_x[p];
		game->map[t][s] = '0';
		if (game->keycode_enemy[p] == KEY_D)
		{
			game->map[t][s + 1] = 'G';
			game->e_pos_y[p] = t;
			game->e_pos_x[p] = s + 1;
		}
		if (game->keycode_enemy[p] == KEY_A)
		{
			game->map[t][s - 1] = 'G';
			game->e_pos_y[p] = t;
			game->e_pos_x[p] = s - 1;
		}
		if (game->keycode_enemy[p] == KEY_S)
		{
			game->map[t + 1][s] = 'G';
			game->e_pos_y[p] = t + 1;
			game->e_pos_x[p] = s;
		}
		if (game->keycode_enemy[p] == KEY_W)
		{
			game->map[t - 1][s] = 'G';
			game->e_pos_y[p] = t - 1;
			game->e_pos_x[p] = s;
		}
		printf("enemy moved back position: %d ---- [%d][%d]\n", p, game->e_pos_y[p], game->e_pos_x[p]);
		p++;
	}
}

void	ft_next_enemy_position(t_map *game, int	p)
{
	int t;
	int s;

	game->enemy_moved++;					//enemy_moved = 1;
	t = game->e_pos_y[p];					// current pposition
	s = game->e_pos_x[p];
	game->e_pos_y_last[p] = game->e_pos_y[p];		//save the last position
	game->e_pos_x_last[p] = game->e_pos_x[p];
	if (game->keycode_enemy[p] == 99 || game->enemy_moved == 0)		//enemy moved == 0?????
		game->map[t][s] = 'G';
	else
	{
		game->map[t][s] = '0';
		if (game->keycode_enemy[p] == KEY_D)		//save the next position
		{
			game->map[t][s + 1] = 'G';
			game->e_pos_y_next[p] = t;
			game->e_pos_x_next[p] = s + 1;
		}
		if (game->keycode_enemy[p] == KEY_A)
		{
			game->map[t][s - 1] = 'G';
			game->e_pos_y_next[p] = t;
			game->e_pos_x_next[p] = s - 1;
		}
		if (game->keycode_enemy[p] == KEY_S)
		{
			game->map[t + 1][s] = 'G';
			game->e_pos_y_next[p] = t + 1;
			game->e_pos_x_next[p] = s;
		}
		if (game->keycode_enemy[p] == KEY_W)
		{
			game->map[t - 1][s] = 'G';
			game->e_pos_y_next[p] = t - 1;
			game->e_pos_x_next[p] = s;
		}
		printf("enemy next position: %d ---- [%d][%d]\n", p, game->e_pos_y_next[p], game->e_pos_x_next[p]);
	}
}

/* Check if the enemy can move west, e.g. the next field is not a collectible, not
the exit and no wall. */
int ft_check_e_move_west(t_map *game, int p)
{
	int t;
	int s;

	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t][s - 1] == '1') || (game->map[t][s - 1] == 'C')
		|| (game->map[t][s - 1] == 'E'))
		return (-1);
	game->keycode_enemy[p] = KEY_A;
	return (0);
}

/* Check if the enemy can move south, e.g. the next field is not a collectible, not
the exit and no wall. */
int ft_check_e_move_south(t_map *game, int p)
{
	int t;
	int s;

	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t + 1][s] == '1') || (game->map[t + 1][s] == 'C')
		|| (game->map[t + 1][s] == 'E'))
		return (-1);
	game->keycode_enemy[p] = KEY_S;
	return (0);
}

/* Check if the enemy can move east, e.g. the next field is not a collectible, not
the exit and no wall. */
int ft_check_e_move_east(t_map *game, int p)
{
	int t;
	int s;

	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t][s + 1] == '1') || (game->map[t][s + 1] == 'C')
		|| (game->map[t][s + 1] == 'E'))
		return (-1);
	game->keycode_enemy[p] = KEY_D;
	return (0);
}

/* Check if the enemy can move north, e.g. the next field is not a collectible, not
the exit and no wall. */
int ft_check_e_move_north(t_map *game, int p)
{
	int t;
	int s;

	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t - 1][s] == '1') || (game->map[t - 1][s] == 'C')
		|| (game->map[t - 1][s] == 'E'))
		return (-1);
	game->keycode_enemy[p] = KEY_W;
	return (0);
}

/* Randomly generate the enemy's movement, with % 4 and assign 0-3 a
direction (north, south, west, east) and test if the enemy can go there. */
int ft_generate_e_move(t_map *game, int p)
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
	int p;
	int flag;
	int e_move;

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
		printf("enemy current position: %d ---- [%d][%d]\n", p, game->e_pos_y[p], game->e_pos_x[p]);
		ft_next_enemy_position(game, p);
		p++;
	}
}
