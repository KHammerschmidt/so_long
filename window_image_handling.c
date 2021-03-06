/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_image_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:01:05 by khammers          #+#    #+#             */
/*   Updated: 2021/11/02 14:32:10 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Memory area for all mlx files regarding the player is allocated and the
respective img-index linked the the xpm file. */
static void	ft_load_player_images(t_struct *so_long)
{
	so_long->img[4] = ft_calloc(1, sizeof(t_img));
	so_long->img[4]->img = mlx_xpm_file_to_image(so_long->vars.mlx, IMG_W_EAST,
			&(so_long->img[4]->width), &(so_long->img[4]->height));
	so_long->img[5] = ft_calloc(1, sizeof(t_img));
	so_long->img[5]->img = mlx_xpm_file_to_image(so_long->vars.mlx, IMG_D_EAST,
			&(so_long->img[5]->width), &(so_long->img[5]->height));
	so_long->img[6] = ft_calloc(1, sizeof(t_img));
	so_long->img[6]->img = mlx_xpm_file_to_image(so_long->vars.mlx, IMG_W_WEST,
			&(so_long->img[6]->width), &(so_long->img[6]->height));
	so_long->img[7] = ft_calloc(1, sizeof(t_img));
	so_long->img[7]->img = mlx_xpm_file_to_image(so_long->vars.mlx, IMG_D_WEST,
			&(so_long->img[7]->width), &(so_long->img[7]->height));
}

/* Memory area for mlx files is allocated and the respective img-index linked
the the xpm file. */
static void	ft_load_images(t_struct *so_long)
{
	so_long->img[0] = ft_calloc(1, sizeof(t_img));
	so_long->img[0]->img = mlx_xpm_file_to_image(so_long->vars.mlx,
			IMG_TILE_MUD, &(so_long->img[0]->width),
			&(so_long->img[0]->height));
	so_long->img[1] = ft_calloc(1, sizeof(t_img));
	so_long->img[1]->img = mlx_xpm_file_to_image(so_long->vars.mlx, IMG_WALL,
			&(so_long->img[1]->width), &(so_long->img[1]->height));
	so_long->img[2] = ft_calloc(1, sizeof(t_img));
	so_long->img[2]->img = mlx_xpm_file_to_image(so_long->vars.mlx,
			IMG_COLLECTIBLE, &(so_long->img[2]->width),
			&(so_long->img[2]->height));
	so_long->img[3] = ft_calloc(1, sizeof(t_img));
	so_long->img[3]->img = mlx_xpm_file_to_image(so_long->vars.mlx, IMG_EXIT,
			&(so_long->img[3]->width), &(so_long->img[3]->height));
	ft_load_player_images(so_long);
}

/* Printing the game instructions in the upper left corner of the window, onto
the wall in white colour. */
void	ft_game_instructions(t_struct *so_long)
{
	mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win, 10, 20,
		0xFFFFFFFF, GAME_INSTRUCTIONS_1);
	mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win, 10, 35,
		0xFFFFFFFF, GAME_INSTRUCTIONS_2);
}

void	ft_image_handling(t_struct *so_long)
{
	so_long->vars.mlx_win = mlx_new_window(so_long->vars.mlx,
			so_long->vars.window_width, so_long->vars.window_height,
			GAME_TITLE);
	ft_load_images(so_long);
	ft_build_map(so_long);
	ft_game_instructions(so_long);
}
