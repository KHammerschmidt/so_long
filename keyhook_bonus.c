/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 17:29:32 by khammers          #+#    #+#             */
/*   Updated: 2021/10/21 16:34:47 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

/* Function prints the number of player moves on the window. */
void	ft_print_moves_on_screen(t_struct *so_long)
{
	char	*str;

	str = ft_itoa(so_long->player.number_of_moves);
	ft_game_instructions(so_long);
	mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win, 10, 50,
		0xFFFFFFFF, "Moves: ");
	mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win, 55, 50,
		0xFFFFFFFF, str);
	free(str);
}

/* When the game is over (player entered exit or an enemy is hit) this function
counts the player moves for the last time, rebuilds the map and prints the respective
WINNER/LOOSER message on the window. */
void	ft_game_over(t_struct *so_long)
{
	so_long->player.still_playing++;
	if (so_long->keyboard == KEY_A || so_long->keyboard == KEY_S
		|| so_long->keyboard == KEY_D || so_long->keyboard == KEY_W)
		so_long->player.number_of_moves++;
	ft_build_map(so_long);
	if (so_long->game.counter_collectible != 0 || so_long->player.enemy_flag == 99)
	{
		mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win,
			so_long->vars.window_mid_width - 80,
			so_long->vars.window_mid_height, 0xFFFFFFFF, LOOSER_MESSAGE_1);
		mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win,
			so_long->vars.window_mid_width - 140, so_long->vars.window_mid_height
			+ 20, 0xFFFFFFFF, LOOSER_MESSAGE_2);
	}
	else
		mlx_string_put(so_long->vars.mlx, so_long->vars.mlx_win,
			so_long->vars.window_mid_width - (95), so_long->vars.window_mid_height,
			0xFFFFFFFF, WINNER_MESSAGE);
}

/* Closes and frees all necessities when ESC, Q or red X are pressed, calls
ft_enemy_movement() and ft_move() while the player is still playing for
player movement/ending the game. Then it prints the moves on the window by
calling ft_print_moves_on_screen(). */
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
		if (keycode == KEY_A || keycode == KEY_S || keycode == KEY_W || keycode == KEY_D)
		{
			ft_enemy_movement(&so_long->game);
			if (ft_move(so_long, keycode) == (-1))
			{
				ft_move_enemy_back(&so_long->game);
				ft_game_over(so_long);
			}
			ft_print_moves_on_screen(so_long);
		}
	}
	return (0);
}