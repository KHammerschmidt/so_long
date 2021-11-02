/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:14:08 by katharinaha       #+#    #+#             */
/*   Updated: 2021/11/02 19:53:36 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Frees memory area allocated to the game's images. */
static void	ft_free_images(t_struct *so_long)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		mlx_destroy_image(so_long->vars.mlx, so_long->img[i]->img);
		free(so_long->img[i]);
		so_long->img[i] = NULL;
		i++;
	}
}

/* Frees memory area used to save gamefield in 2D array. */
static void	ft_free_gamefield(t_struct *so_long)
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

/* Called when the game is over to free all memory area (images and
gamefield) and close the game. */
int	ft_close(t_struct *so_long)
{
	if (so_long->img[0])
		ft_free_images(so_long);
	ft_free_gamefield(so_long);
	exit(0);
	return (0);
}
