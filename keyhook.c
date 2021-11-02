/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:29:32 by khammers          #+#    #+#             */
/*   Updated: 2021/11/02 14:29:53 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* When the game is over (player entered exit or an enemy is hit) this function
counts the player moves for the last time, rebuilds the map and prints the
respective WINNER/LOOSER message on the window. */
static void	ft_game_over(t_struct *so_long)
{
	so_long->player.still_playing++;
	ft_count_player_moves(so_long);
	ft_build_map(so_long);
	if (so_long->game.counter_collectible != 0)
	{
		mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win,
			so_long->vars.window_mid_width - 80,
			so_long->vars.window_mid_height, 0xFFFFFFFF, LOOSER_MESSAGE_1);
		mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win,
			so_long->vars.window_mid_width - 140,
			so_long->vars.window_mid_height + 20, 0xFFFFFFFF, LOOSER_MESSAGE_2);
	}
	else
		mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win,
			so_long->vars.window_mid_width - (95),
			so_long->vars.window_mid_height, 0xFFFFFFFF, WINNER_MESSAGE);
}

/* Closes and frees all necessities when ESC, Q or red X are pressed, calls
ft_move() while the player is still playing for player movement and ending the
game when necessary. For every move the game instructions are being printed on
the screen. */
int	key_hook(int keycode, t_struct *so_long)
{
	so_long->keyboard = keycode;
	if (keycode == 0x35 || keycode == 12)
	{
		mlx_destroy_window(so_long->vars.mlx, so_long->vars.mlx_win);
		ft_close(so_long);
	}
	if (so_long->player.still_playing == 0)
	{
		if (ft_move(so_long, keycode) == (-1))
			ft_game_over(so_long);
	}
	ft_game_instructions(so_long);
	return (0);
}
