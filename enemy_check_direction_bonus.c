/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_check_direction_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:21:21 by khammers          #+#    #+#             */
/*   Updated: 2021/10/24 21:27:53 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Check if the enemy can move west, e.g. the next field is not a collectible
not the exit and no wall. */
int	ft_check_e_move_west(t_map *game, int p)
{
	int	t;
	int	s;
	int	i;

	i = 0;
	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t][s - 1] == '1') || (game->map[t][s - 1] == 'C')
		|| (game->map[t][s - 1] == 'E') || (game->map[t][s - 1] == 'G'))
		return (-1);
	game->keycode_enemy[p] = KEY_A;
	return (0);
}

/* Check if the enemy can move south, e.g. the next field is not a collectible,
not the exit and no wall. */
int	ft_check_e_move_south(t_map *game, int p)
{
	int	t;
	int	s;
	int	i;

	i = 0;
	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t + 1][s] == '1') || (game->map[t + 1][s] == 'C')
		|| (game->map[t + 1][s] == 'E') || (game->map[t + 1][s] == 'G'))
		return (-1);
	game->keycode_enemy[p] = KEY_S;
	return (0);
}

/* Check if the enemy can move east, e.g. the next field is not a collectible,
not the exit and no wall. */
int	ft_check_e_move_east(t_map *game, int p)
{
	int	t;
	int	s;
	int	i;

	i = 0;
	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t][s + 1] == '1') || (game->map[t][s + 1] == 'C')
		|| (game->map[t + 1][s] == 'E') || (game->map[t][s + 1] == 'G'))
		return (-1);
	game->keycode_enemy[p] = KEY_D;
	return (0);
}

/* Check if the enemy can move north, e.g. the next field is not a collectible,
not the exit and no wall. */
int	ft_check_e_move_north(t_map *game, int p)
{
	int	t;
	int	s;
	int	i;

	i = 0;
	t = game->e_pos_y[p];
	s = game->e_pos_x[p];
	if ((game->map[t - 1][s] == '1') || (game->map[t - 1][s] == 'C')
		|| (game->map[t - 1][s] == 'E') || (game->map[t - 1][s] == 'G'))
		return (-1);
	game->keycode_enemy[p] = KEY_W;
	return (0);
}
