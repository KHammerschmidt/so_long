/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 19:41:50 by katharinaha       #+#    #+#             */
/*   Updated: 2021/10/19 12:38:09 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Increment the number of movements made by the player and write it to the
terminal. */
void	ft_count_player_moves(t_struct *so_long)
{
	if (so_long->keyboard == KEY_A || so_long->keyboard == KEY_S
		|| so_long->keyboard == KEY_D || so_long->keyboard == KEY_W)
	{
		so_long->player.number_of_moves++;
		ft_putnbr_fd(so_long->player.number_of_moves, 1);
		if (so_long->player.number_of_moves == 1)
			ft_putstr_fd(" Move\n", 1);
		else
			ft_putstr_fd(" Moves\n", 1);
	}
}

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
void	ft_check_p_move(t_struct *so_long, int j, int i)
{
	if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] != '1')
	|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] != '1')
	|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] != '1')
	|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] != '1'))
	{
		if ((so_long->keyboard == KEY_D && so_long->game.map[j][i + 1] == 'C')
		|| (so_long->keyboard == KEY_A && so_long->game.map[j][i - 1] == 'C')
		|| (so_long->keyboard == KEY_S && so_long->game.map[j + 1][i] == 'C')
		|| (so_long->keyboard == KEY_W && so_long->game.map[j - 1][i] == 'C'))
			so_long->game.counter_collectible--;
		ft_change_position(so_long, j, i);
		ft_count_player_moves(so_long);
	}
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

	j = so_long->player.player_position_y;
	i = so_long->player.player_position_x;
	so_long->keyboard = keycode;
	if (so_long->keyboard == KEY_D)
		so_long->keyboard_last = KEY_D;
	if (so_long->keyboard == KEY_A)
		so_long->keyboard_last = KEY_A;
	if (ft_check_game_over(so_long, j, i) == -1)
		return (-1);
	ft_check_p_move(so_long, j, i);
	ft_build_map(so_long);
	return (0);
}
