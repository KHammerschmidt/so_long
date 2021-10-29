/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 19:54:45 by khammers          #+#    #+#             */
/*   Updated: 2021/10/29 16:50:11 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Function to let enemy walk north-south. */
int	ft_even_nbrs(t_map *game, int p, int t, int s)
{
	int	nbr_rd;
	int	incr;

	nbr_rd = rand();
	if (nbr_rd % 2 == 0)
		incr = 1;
	else
		incr = -1;
	if (game->map[t + incr][s] != 'E' && game->map[t + incr][s] != 'C'
		&& game->map[t + incr][s] != 'G' && game->map[t + incr][s] != '1')
	{
		game->map[t][s] = '0';
		if (game->map[t + incr][s] == 'P')
			return (-1);
		game->map[t + incr][s] = 'G';
		game->e_pos_y[p] = t + incr;
	}
	else
		game->map[t][s] = 'G';
	game->e_pos_y_last[p] = t;
	game->e_pos_x_last[p] = s;
	return (0);
}

/* Function to let enemy walk east-west. */
int	ft_odd_nbrs(t_map *game, int p, int t, int s)
{
	int	nbr_rd;
	int	incr;

	nbr_rd = rand();
	if (nbr_rd % 2 == 0)
		incr = 1;
	else
		incr = -1;
	if (game->map[t][s + incr] != 'E' && game->map[t][s + incr] != 'C'
		&& game->map[t][s + incr] != 'G' && game->map[t][s + incr] != '1')
	{
		game->map[t][s] = '0';
		if (game->map[t][s + incr] == 'P')
			return (-1);
		game->map[t][s + incr] = 'G';
		game->e_pos_x[p] = s + incr;
	}
	else
		game->map[t][s] = 'G';
	game->e_pos_y_last[p] = t;
	game->e_pos_x_last[p] = s;
	return (0);
}

/* For each enemy the index (p) decides if the enemy moves
north-south or east-west. */
int	ft_enemy_movement(t_map *game)
{
	int	p;
	int	t;
	int	s;

	p = 0;
	while (p < game->counter_enemy)
	{
		t = game->e_pos_y[p];
		s = game->e_pos_x[p];
		if ((p % 2) == 0)
		{
			if (ft_even_nbrs(game, p, t, s) == -1)
				return (-1);
		}
		else
		{
			if (ft_odd_nbrs(game, p, t, s) == -1)
				return (-1);
		}
		p++;
	}
	return (0);
}
