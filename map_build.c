/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katharinahammerschmidt <katharinahammer    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:34:56 by khammers          #+#    #+#             */
/*   Updated: 2021/11/01 20:05:09 by katharinaha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* While the player is still playing this function returns the player facing
in a direction, depending on the key pressed now and the previous one. */
t_img	*ft_sprite_animation_still_playing(t_struct *so_long)
{
	if (so_long->keyboard == KEY_D)
		return (so_long->img[4]->img);
	else if (so_long->keyboard == KEY_A)
		return (so_long->img[6]->img);
	else if (so_long->keyboard_last == KEY_D || so_long->keyboard_last == 99)
		return (so_long->img[4]->img);
	else if (so_long->keyboard_last == KEY_A)
		return (so_long->img[6]->img);
	return (0);
}

/* If the game ends, this function differentiates between a winning player
or a loosing one and returns the player alive or dead, facing in the
direction of the last movement. */
t_img	*ft_sprite_animation_not_playing(t_struct *so_long)
{
	if (so_long->game.counter_collectible == 0)
		return (so_long->img[0]->img);
	else if (so_long->game.counter_collectible != 0)
	{
		if (so_long->keyboard == KEY_A)
			return (so_long->img[7]->img);
		else if (so_long->keyboard == KEY_D)
			return (so_long->img[5]->img);
		else if (so_long->keyboard_last == KEY_A)
			return (so_long->img[7]->img);
		else
			return (so_long->img[5]->img);
	}
	return (0);
}

/* The IMG of the corresponding map character is returned to build the map.
In case of a 'P' a sprite animation function is called, depending if the
player is still playing or not, e.g. image = alive or dead player. */
void	*ft_which_img(t_struct *so_long, int x, int y)
{
	if (so_long->game.map[y][x] == 'P')
	{
		if (so_long->keyboard == 99)
			return (so_long->img[4]->img);
		if (so_long->player.still_playing == 0)
			return (ft_sprite_animation_still_playing(so_long));
		if (so_long->player.still_playing == 1)
			return (ft_sprite_animation_not_playing(so_long));
	}
	if (so_long->game.map[y][x] == 'E')
		return (so_long->img[3]->img);
	if (so_long->game.map[y][x] == 'C')
		return (so_long->img[2]->img);
	if (so_long->game.map[y][x] == '1')
		return (so_long->img[1]->img);
	if (so_long->game.map[y][x] == '0')
		return (so_long->img[0]->img);
	return (0);
}

/* In order to (re-)build the gamefield on the window it is cleared first. Then
in a loop it is build row by row and column by column. The IMG of free space is
put below every image of a 'PCE', then the function ft_which_img() is called.*/
void	ft_build_map(t_struct *so_long)
{
	int	x;
	int	y;

	mlx_clear_window(so_long->vars.mlx, so_long->vars.mlx_win);
	y = 0;
	while (y < so_long->game.map_height)
	{
		x = 0;
		while (x < so_long->game.map_width)
		{
			if (so_long->game.map[y][x] != '1')
				mlx_put_image_to_window(so_long->vars.mlx,
					so_long->vars.mlx_win, so_long->img[0]->img,
					so_long->vars.img_size * x, so_long->vars.img_size * y);
			mlx_put_image_to_window(so_long->vars.mlx, so_long->vars.mlx_win,
				ft_which_img(so_long, x, y), so_long->vars.img_size * x,
				so_long->vars.img_size * y);
			x++;
		}
		y++;
	}
}
