/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:41:50 by katharinaha       #+#    #+#             */
/*   Updated: 2021/10/21 17:18:48 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* The pressed keys W, D, S and A indicate the direction in which the player
moves (north, east, south and west). The initial player position is set to free
space and the new player position set. */
void	ft_change_position(t_struct *so_long, int j, int i)
{
	so_long->game.map[j][i] = '0';
	if (so_long->keyboard == KEY_D)
		so_long->game.map[j][i + 1] = 'P';
	if (so_long->keyboard == KEY_A)
		so_long->game.map[j][i - 1] = 'P';
	if (so_long->keyboard == KEY_S)
		so_long->game.map[j + 1][i] = 'P';
	if (so_long->keyboard == KEY_W)
		so_long->game.map[j - 1][i] = 'P';
	ft_player_position(so_long);
}

/* Test if player can move in direction of keycode, if yes test if there is an
exit, an enemy or a collectible that the player then collects. If any movement
results into the player's death, flag is incremented and -1 returned. */
int	ft_check_p_move(t_struct *so_long, int j, int i)
{
	if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] != '1')
	|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] != '1')
	|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] != '1')
	|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] != '1'))
	{
		if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] == 'G')
		|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] == 'G')
		|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] == 'G')
		|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] == 'G'))
		{
			printf("On this position is an enemy!\n");
			so_long->player.enemy_flag = 99;
		}
		if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] == 'C')
		|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] == 'C')
		|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] == 'C')
		|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] == 'C'))
			so_long->game.counter_collectible--;
		so_long->player.number_of_moves++;
		if (so_long->player.enemy_flag == 99)
			return (-1);
		ft_change_position(so_long, j, i);
	}
	else if (so_long->game.enemy_moved == 1)
		ft_move_enemy_back(&so_long->game);
	return (0);
}

/* It is tested for each enemy, if an enemy and the player exchange positions
by walking through each other, which leads to a dead character, resulting in
a return value of -1. */
int	ft_check_enemy_collision(t_struct *so_long)
{
	int	p;

	p = 0;
	while (p < so_long->game.counter_enemy)
	{
		if (so_long->player.player_position_y == so_long->game.e_pos_y[p]
		&& so_long->player.player_position_x == so_long->game.e_pos_x[p])
		{
			printf("player moves into enemy!\n");
			so_long->player.enemy_flag = 99;
		}
		if ((so_long->game.e_pos_y[p] == so_long->player.player_position_last_y
		&& so_long->game.e_pos_x[p] == so_long->player. player_position_last_x)
		&& so_long->game.e_pos_y_last[p] == so_long->player.player_position_y
		&& so_long->game.e_pos_y_last[p] == so_long->player.player_position_x)
			{
			printf("player and enemy move into each other!\n");
			so_long->player.enemy_flag = 99;
		}
		p++;
	}
	if (so_long->player.enemy_flag == 99)
	{
		// ft_move_enemy_back(&so_long->game);
		return (-1);
	}
	ft_support_enemy_move(&so_long->game);
	return (0);
}

/* Check is the pressed key leads the player into the game's exit, if so
return -1, otherwise 0. */
int	ft_check_game_over(t_struct *so_long, int j, int i)
{
	if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] == 'E')
	|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] == 'E')
	|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] == 'E')
	|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] == 'E'))
		return (-1);
	return (0);
}

/* Test if keycode input represents valid movement with keys A, S, D & W
and save the last direction the player is facing. */
int	ft_save_keycode_move(int keycode, t_struct *so_long)
{
	if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_W
		|| keycode == KEY_D)
		{
			so_long->keyboard = keycode;
			if (so_long->keyboard == KEY_D)
				so_long->keyboard_last = KEY_D;
			if (so_long->keyboard == KEY_A)
				so_long->keyboard_last = KEY_A;
			return (0);
		}
	return (-1);
}

/* The player's position is saved in j & i and the position the player is facing,
saved in so_long->keyboard_last. The function tests if the player moves into an
exit (ft_check_game_over()), if the player can move into the direction
(ft_check_p_move()) and if the player collides with an enemy
(ft_check_enemy_collision()). In these cases a -1 is returned which triggers
ft_game_over(), otherwise the map is rebuilt and 0 returned. */
int	ft_move(t_struct *so_long, int keycode)
{
	int	j;
	int	i;

	if (ft_save_keycode_move(keycode, so_long) == 0)			//valid input keycode
	{
		j = so_long->player.player_position_y;
		i = so_long->player.player_position_x;

		if (ft_check_game_over(so_long, j, i) == -1)			//next move is into 'E"
			return (-1);
		if (ft_check_p_move(so_long, j, i) == 0)				//is there a wall? is there a "G" or 'C'?
		{
			if (ft_check_enemy_collision(so_long) == (-1))
				return (-1);
			ft_build_map(so_long);
		}
		else
			return (-1);
	}
	return (0);
}