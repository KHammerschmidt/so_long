/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error_handling_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 12:29:22 by khammers          #+#    #+#             */
/*   Updated: 2021/11/02 14:30:53 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Loop through 2D array 'map' and check if all outside characters represent a
wall, respectively the character '1'. */
static int	ft_check_surrounding_walls(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (y <= (game->map_height - 1))
	{
		x = 0;
		while (x <= (game->map_width - 1))
		{
			if (y == 0 && game->map[y][x] != '1')
				return (-1);
			if ((y == game->map_height - 1) && game->map[y][x] != '1')
				return (-1);
			if (x == 0 && game->map[y][x] != '1')
				return (-1);
			if ((x == game->map_width - 1) && game->map[y][x] != '1')
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

/* Loop through 2D array 'map' and check if all necessary characters appear.
At least 1 starting position, 1 exit and one collectible. If not return -1 which
triggers an error message. */
static int	ft_check_necessary_map_characters(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < (game->map_height - 1))
	{
		x = 0;
		while (x < (game->map_width - 1))
		{
			if (game->map[y][x] == 'P')
				game->counter_player++;
			if (game->map[y][x] == 'E')
				game->counter_exit++;
			if (game->map[y][x] == 'C')
				game->counter_collectible++;
			if (game->map[y][x] == 'G')
				game->counter_enemy++;
			x++;
		}
		y++;
	}
	if (game->counter_player != 1 || game->counter_exit < 1
		|| game->counter_collectible < 1)
		return (-1);
	return (0);
}

/* Loop through 2D array 'map' and check if any forbidden characters
exist besides '01PEGC'. */
static int	ft_check_forbidden_map_characters(t_map *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < (game->map_height - 1))
	{
		x = 0;
		while (x < (game->map_width - 1))
		{
			if (game->map[y][x] != '1' && game->map[y][x] != 'P'
				&& game->map[y][x] != 'E' && game->map[y][x] != 'C'
				&& game->map[y][x] != '0' && game->map[y][x] != 'G')
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

/* Function to check if input map has the correct size and characters. If not an
error message is displayed, -1 returned and the main function calls ft_close() to
free all memory area. */
int	ft_map_errors(t_struct *so_long)
{
	if (ft_check_surrounding_walls(&so_long->game) == -1)
	{
		ft_putstr_fd("Error\nMissing wall for gamefield!\n", 1);
		return (-1);
	}
	if (ft_check_necessary_map_characters(&so_long->game) == -1)
	{
		ft_putstr_fd("Error\nMap doesn't contain necessary characters!\n", 1);
		return (-1);
	}
	if (ft_check_forbidden_map_characters(&so_long->game) == -1)
	{
		ft_putstr_fd("Error\nMap contains unallowed characters!\n", 1);
		return (-1);
	}
	if (so_long->game.map_width <= so_long->game.map_height)
	{
		ft_putstr_fd("Error\nGame field is not rectangular!\n", 1);
		return (-1);
	}
	return (0);
}
