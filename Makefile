# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khammers <khammers@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/22 14:33:38 by khammers          #+#    #+#              #
#    Updated: 2021/10/29 17:05:30 by khammers         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -Wall -Werror -Wextra -L ./srcs/mlx -lmlx -L ./srcs/libft -lft -framework OpenGl -framework AppKit

SRC = main.c \
	input_handling.c \
	get_next_line.c \
	map_error_handling.c \
	map_creation.c \
	player_moves.c \
	map_build.c \
	keyhook.c \
	init_game.c \
	end_game.c \
	window_image_handling.c

SRC_B = main_bonus.c \
	input_handling_bonus.c \
	get_next_line_bonus.c \
	map_error_handling_bonus.c \
	map_creation_bonus.c \
	player_moves_bonus.c \
	map_build_bonus.c \
	keyhook_bonus.c \
	init_game_bonus.c \
	end_game_bonus.c \
	enemy_move_bonus.c \
	window_image_handling_bonus.c

LIBFT_OBJ = ./srcs/libft/libft.a
MLX = ./srcs/mlx/libmlx.a

OBJECTS = $(SRC:.c=.o)
OBJECTS_B = $(SRC_B:.c=.o)

NAME = so_long
all: $(NAME)

NAME_B = so_long_bonus
bonus: $(NAME_B)

$(NAME): $(MLX) $(OBJECTS) $(LIBFT_OBJ)
	$(CC) $(FLAGS) $^ -o $@

$(NAME_B): $(MLX) $(OBJECTS_B) $(LIBFT_OBJ)
	$(CC) $(FLAGS) $^ -o $@

$(MLX):
	make --directory=./srcs/mlx

$(LIBFT_OBJ):
	make --directory=./srcs/libft

clean:
	rm -f $(OBJECTS)
	rm -f $(OBJECTS_B)
	make clean -C ./srcs/libft
	make clean -C ./srcs/mlx

fclean: clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C ./srcs/libft

re: fclean all







# $(NAME) $(OBJECTS_B)
# $(CC) $(FLAGS) -o $(NAME) $(OBJECTS_B) $(FLAGS)

# $(CC) $(FLAGS) -o $(OBJECTS) $(OBJECT_B) $(M$(FLAGS)


# bonus: $(OBJECTS_B) $(MLX) $(LIBFT_OBJ)
# 	make --directory=./srcs/mlx
# 	$(CC) $(FLAGS) -o $(OBJECTS) $(OBJECT_B) $(FLAGS)


# OLD ------------------------------------------
# %.o: %.c
# 	$(CC) -Wall -Werror -Wextra -lmlx -c $< -o $@

# $(NAME): $(OBJ)
# 	$(CC) -Lmlx -lmlx -framework -OpenGL -framework AppKit -o $(NAME)

# $(NAME): $(MLX) $(OBJECTS) $(LIBFT_OBJECTS)
# 	$(CC) $(FLAGS) $^ -o $@ $(LIBFT_OBJECTS)
