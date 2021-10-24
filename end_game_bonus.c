/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:45:37 by katharinaha       #+#    #+#             */
/*   Updated: 2021/10/24 20:29:49 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Frees memory area allocated to the game's images. */
void	ft_free_images(t_struct *so_long)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		mlx_destroy_image(so_long->vars.mlx, so_long->img[i]->img);
		free(so_long->img[i]);
		so_long->img[i] = NULL;
		i++;
	}
}

/* Frees memory area used to save gamefield in 2D array. */
void	ft_free_gamefield(t_struct *so_long)
{
	int	y;

	y = 0;
	while (y < so_long->game.map_height)
	{
		if (so_long->game.map[y] != NULL)
		{
			free (so_long->game.map[y]);
			so_long->game.map[y] = NULL;
		}
		y++;
	}
	if (so_long->game.map[y] != NULL)
	{
		free (so_long->game.map);
		so_long->game.map = NULL;
	}
}

void	ft_free_enemies(t_map *game)
{
	free (game->e_pos_x);
	game->e_pos_x = NULL;
	free (game->e_pos_y);
	game->e_pos_y = NULL;
	free (game->e_pos_x_last);
	game->e_pos_x_last = NULL;
	free (game->e_pos_y_last);
	game->e_pos_y_last = NULL;
	free (game->keycode_enemy);
	game->keycode_enemy = NULL;
}

/* Called when the game is over to free all memory area (images, gamefield
and struct t_enemy) and close the game. */
int	ft_close(t_struct *so_long)
{
	if (so_long->img[0])
		ft_free_images(so_long);
	ft_free_gamefield(so_long);
	if ((so_long->game.e_pos_x) && (so_long->game.e_pos_y)
		&& (so_long->game.e_pos_x_last) && (so_long->game.e_pos_y_last)
		&& (so_long->game.keycode_enemy))
		ft_free_enemies(&so_long->game);
	exit(0);
	return (0);
}
