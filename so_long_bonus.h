/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 14:35:10 by khammers          #+#    #+#             */
/*   Updated: 2021/11/02 14:44:59 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "./srcs/mlx/mlx.h"
# include "./srcs/libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>

# define BUFFER_SIZE 1
# define GAME_TITLE "SO_LONG_BONUS"
# define GAME_INSTRUCTIONS_1 "Help Mindy collect all crystals to pass"
# define GAME_INSTRUCTIONS_2 "the portal! Mind the snowmen! Good luck!"
# define LOOSER_MESSAGE_1 "MINDY FROZE TO DEATH!!!"
# define LOOSER_MESSAGE_2 "YOU SHOULD HAVE COLLECTED ALL CRYSTALS!"
# define WINNER_MESSAGE "YOU WON! CONGRATULATIONS!!!"

/* Define images in .xpm format */
# define IMG_EXIT "./images/Exit_Sign.xpm"
# define IMG_TILE_MUD "./images/Tile_Mud.xpm"
# define IMG_WALL "./images/Box_Wall.xpm"
# define IMG_COLLECTIBLE "./images/Crystal_Collectible.xpm"
# define IMG_W_EAST "./images/W_EAST.xpm"
# define IMG_W_WEST "./images/W_WEST.xpm"
# define IMG_D_EAST "./images/D_EAST.xpm"
# define IMG_D_WEST "./images/D_WEST.xpm"
# define IMG_ENEMY "./images/SnowMan.xpm"

/* Struct 'xpm' for MiniLibX window and image handling */
typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
	int		window_width;
	int		window_height;
	int		window_mid_width;
	int		window_mid_height;
	int		img_size;
}				t_vars;

/* Struct 'img' for handling the game's tiles and sprites sizes */
typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}				t_img;

/* Struct 'game' to read map characters and create gamefield grid */
typedef struct map_coordinates
{
	char	**map;
	int		map_width;
	int		map_height;
	int		counter_collectible;
	int		counter_player;
	int		counter_exit;
	int		counter_enemy;
	int		*e_pos_x;
	int		*e_pos_y;
	int		*e_pos_x_last;
	int		*e_pos_y_last;
	int		*keycode_enemy;
	int		enemy_moved;
}				t_map;

/* Struct 'player' to handle the player's position and continue playing */
typedef struct s_player
{
	int		player_position_x;
	int		player_position_y;
	int		player_position_last_x;
	int		player_position_last_y;
	int		number_of_moves;
	int		still_playing;
	int		enemy_flag;
}				t_player;

/* Struct 'so_long' to pass on all structs in the game */
typedef struct s_struct
{
	t_vars		vars;
	t_img		*img[9];
	t_img		xpm;
	t_map		game;
	t_player	player;
	int			keyboard;
	int			keyboard_last;
	int			game_solved;
}				t_struct;

/* Define all necessar keycodes to distinguish moves during game */
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_Q 12
# define KEY_ESC 0x35

int			main(int argc, char **argv);
int			ft_handle_input(int argc, char **argv);
int			key_hook(int keycode, t_struct *so_long);

/* Functions for image handling & printing text on window */
void		ft_image_handling(t_struct *so_long);
static void	ft_load_images(t_struct *so_long);
static void	ft_load_player_images(t_struct *so_long);
void		ft_game_instructions(t_struct *so_long);
void		ft_print_moves_on_screen(t_struct *so_long);

/* Functions to read, allocate and define map, e.g. the gamefiled */
void		ft_map_init(t_struct *so_long);
void		ft_define_map_size(char *file, t_struct *so_long);
static int	ft_allocate_map_memory(t_struct *so_long);
static void	ft_read_map_grid(char *file, t_struct *so_long);

/* Functions for get_next_line with a BUFFER_SIZE=1  */
char		*get_next_line(int fd);
static char	*ft_get_output(char **line);
static char	*ft_strnjoin(char *s1, char *s2, ssize_t bytes);
static char	*ft_update_char_output(char **line, ssize_t bytes);
static void	ft_free(char **char_stat);

/* Functions to check map specifications made by subject */
int			ft_map_errors(t_struct *so_long);
static int	ft_check_necessary_map_characters(t_map *game);
static int	ft_check_forbidden_map_characters(t_map *game);
static int	ft_check_surrounding_walls(t_map *game);

/* Functions for MiniLibX window and image handling */
void		ft_load_images(t_struct *so_long);
void		ft_build_map(t_struct *so_long);
static void	*ft_which_img(t_struct *so_long, int x, int y);

/* Functions to move the player */
int			ft_move(t_struct *so_long, int keycode);
static int	ft_check_game_over(t_struct *so_long, int j, int i);
static int	ft_check_p_move(t_struct *so_long, int j, int i);
static void	ft_change_position(t_struct *so_long, int j, int i);
void		ft_count_player_moves(t_struct *so_long);

/* Functions to initialise variables */
void		ft_game_init(t_struct *so_long);
void		ft_player_position(t_struct *so_long);

/* Functions to end the game */
static void	ft_game_over(t_struct *so_long);
int			ft_close(t_struct *so_long);
static void	ft_free_images(t_struct *so_long);
static void	ft_free_gamefield(t_struct *so_long);

/* Functions to handle the random enemy movement. */
static void	ft_e_memory_allocation(t_map *game);
int			ft_enemy_movement(t_map *game);
static int		ft_odd_nbrs(t_map *game, int p, int t, int s);
static int		ft_even_nbrs(t_map *game, int p, int t, int s);

#endif