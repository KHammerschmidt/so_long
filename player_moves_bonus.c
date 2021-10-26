/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:41:50 by katharinaha       #+#    #+#             */
/*   Updated: 2021/10/26 13:21:25 by khammers         ###   ########.fr       */
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

int	ft_enemy_last(t_struct *so_long, int j, int i)
{
	int	p;

	p = 0;
	while (p < so_long->game.counter_enemy)
	{
		printf("player last: [%d[%d]\n", so_long->player.player_position_last_y, so_long->player.player_position_last_x);
		printf("player now: [%d[%d]\n", so_long->player.player_position_y, so_long->player.player_position_x);
		printf("enemy %d last: [%d][%d]\n", p, so_long->game.e_pos_y_last[p], so_long->game.e_pos_x_last[p]);
		printf("enemy %d now: [%d][%d]\n", p, so_long->game.e_pos_y[p], so_long->game.e_pos_x[p]);
		printf("\n");
		if (so_long->keyboard == KEY_D)
		{
			if (j == so_long->game.e_pos_y[p] && (i + 1) == so_long->game.e_pos_x[p]
			&& so_long->game.e_pos_y_last[p] == so_long->player.player_position_last_y
			&& so_long->game.e_pos_x_last[p] == so_long->player.player_position_last_x)
			{
				printf("1\n");
				return (-1);
			}
		}
		if (so_long->keyboard == KEY_A)
		{
			if (j == so_long->game.e_pos_y[p] && (i - 1) == so_long->game.e_pos_x[p]
			&& so_long->game.e_pos_y_last[p] == so_long->player.player_position_last_y
			&& so_long->game.e_pos_x_last[p] == so_long->player.player_position_last_x)
			{
				printf("2\n");
				return (-1);
			}
		}
		if (so_long->keyboard == KEY_S)
		{
			if ((j + 1) == so_long->game.e_pos_y[p] && i == so_long->game.e_pos_x[p]
			&& so_long->game.e_pos_y_last[p] == so_long->player.player_position_last_y
			&& so_long->game.e_pos_x_last[p] == so_long->player.player_position_last_x)
			{
				printf("3\n");
				return (-1);
			}
		}
		if (so_long->keyboard == KEY_W)
		{
			if ((j - 1) == so_long->game.e_pos_y[p] && i == so_long->game.e_pos_x[p]
			&& so_long->game.e_pos_y_last[p] == so_long->player.player_position_last_y
			&& so_long->game.e_pos_x_last[p] == so_long->player.player_position_last_x)
			{
				printf("4\n");
				return (-1);
			}
		}
		p++;
	}
	return (0);
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
		so_long->player.number_of_moves++;
		ft_enemy_movement(&so_long->game);
		if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] == 'G')
		|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] == 'G')
		|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] == 'G')
		|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] == 'G'))
			so_long->player.enemy_flag = 99;
		// if (ft_enemy_last(so_long, j, i) == -1)
		// 	so_long->player.enemy_flag = 99;
		if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] == 'C')
		|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] == 'C')
		|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] == 'C')
		|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] == 'C'))
			so_long->game.counter_collectible--;

		if (so_long->player.enemy_flag == 99)
			return (-1);
		ft_change_position(so_long, j, i);
	}
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

/* The player's position is saved in j & i and the position the player is
facing, saved in so_long->keyboard_last. The function tests if the player
moves into an exit (ft_check_game_over()), if the player can move into the
direction (ft_check_p_move()) and if the player collides with an enemy
(ft_check_enemy_collision()). In these cases a -1 is returned which triggers
ft_game_over(), otherwise the map is rebuilt and 0 returned. */
int	ft_move(t_struct *so_long, int keycode)
{
	int	j;
	int	i;

	if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_W
		|| keycode == KEY_D)
	{
		so_long->keyboard = keycode;
		if (so_long->keyboard == KEY_D)
			so_long->keyboard_last = KEY_D;
		if (so_long->keyboard == KEY_A)
			so_long->keyboard_last = KEY_A;
		j = so_long->player.player_position_y;
		i = so_long->player.player_position_x;
		if (ft_check_game_over(so_long, j, i) == -1
			|| ft_check_p_move(so_long, j, i) == -1)
			return (-1);
		ft_build_map(so_long);
	}
	return (0);
}





/* Test if player and enemy exchanged positions, thereby walking through
each other which causes the player to die. */
// int	ft_check_enemy_collision(t_struct *so_long, int j, int i)
// {
// 	int	p;

// 	p = 0;
// 	while (p < so_long->game.counter_enemy)
// 	{
// 		if ((so_long->keyboard == KEY_D)
// 		{
// 			j = so_long->game.e_pos_y[p];
// 			i + 1 = so_long->game.e_pos_x[p];
// 		}
// 	|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] != '1')
// 	|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] != '1')
// 	|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] != '1'))


// 		printf("player last: [%d[%d]\n", so_long->player.player_position_last_y, so_long->player.player_position_last_x);
// 		printf("player now: [%d[%d]\n", so_long->player.player_position_y, so_long->player.player_position_x);
// 		printf("\n");
// 		printf("enemy %d last: [%d][%d]\n", p, so_long->game.e_pos_y_last[p], so_long->game.e_pos_x_last[p]);
// 		printf("enemy %d now: [%d][%d]\n", p, so_long->game.e_pos_y[p], so_long->game.e_pos_x[p]);
// 		printf("\n");
// 		if (so_long->player.player_position_y == so_long->game.e_pos_y_last[p]
// 		&& so_long->player.player_position_x == so_long->game.e_pos_x_last[p])
// 		{
// 			so_long->player.enemy_flag = 99;
// 			return (-1);
// 		}
// 		if (so_long->player.player_position_y == so_long->game.e_pos_y_last[p]
// 		&& so_long->player.player_position_x == so_long->game.e_pos_x_last[p]
// 		&& so_long->player.player_position_last_y == so_long->game.e_pos_y[p]
// 		&& so_long->player.player_position_last_x == so_long->game.e_pos_x[p])
// 			so_long->player.enemy_flag = 99;
// 		p++;
// 	}
// 	if (so_long->player.enemy_flag == 99)
// 		return (-1);
// 	return (0);
// }