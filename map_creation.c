/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:32:35 by khammers          #+#    #+#             */
/*   Updated: 2021/10/19 18:36:14 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Function to initialise all variables necessary to build the gamefield-map
coordinate system. Initialising keyboard to flag = 99 to handle corner-case of
moving into the exit_into an enemy with the first move. */
void	ft_map_init(t_struct *so_long)
{
	so_long->game.map_width = 0;
	so_long->game.map_height = 0;
	so_long->game.counter_collectible = 0;
	so_long->game.counter_player = 0;
	so_long->game.counter_exit = 0;
	so_long->keyboard = 99;
	so_long->keyboard_last = 99;
}

/* Reading the .ber file and saving each character in a designated coordinate
system. Reading with a nested loop row per row for every column of .ber file.
In between each gnl call the char * is freed. */
void	ft_read_map_grid(char *file, t_struct *so_long)
{
	int		fd;
	int long		x;
	int long		y;
	char	*horizontal_line;

	fd = open(file, O_RDONLY);
	if (fd == -1 || fd == 0)
		ft_close(so_long);
	y = 0;
	x = 0;
	horizontal_line = ft_calloc(so_long->game.map_width + 1, sizeof(char));
	if (!horizontal_line)
		ft_close(so_long);
	while (horizontal_line != NULL && y < so_long->game.map_height)
	{
		horizontal_line = get_next_line(fd);
		x = 0;
		while (x < so_long->game.map_width)
		{
			so_long->game.map[y][x] = horizontal_line[x];
			x++;
		}
		free(horizontal_line);
		y++;
	}
	close(fd);
}

/* Memory allocation happens first column-wise for char *, then for every
row of the .ber file. If memory allocation fails an error message is printed
and function ft_close() called. */
int	ft_allocate_map_memory(t_struct *so_long)
{
	int	i;

	i = 0;
	so_long->game.map = (char **)ft_calloc(so_long->game.map_height,
			sizeof(char *));
	if (so_long->game.map == NULL)
	{
		ft_putstr_fd("Error\nAllocation failed!\n", 1);
		ft_close(so_long);
	}
	while (i < so_long->game.map_height)
	{
		so_long->game.map[i] = (char *)ft_calloc(so_long->game.map_width,
				sizeof(char));
		if (so_long->game.map[i] == NULL)
		{
			ft_putstr_fd("Error\nAllocation failed!\n", 1);
			ft_close(so_long);
		}
		i++;
	}
	return (0);
}

/* In order to allocate memory area for the gamefield, the function checks if
fd is readable and counts the columns and width of '.ber' map using
get_next_line. If this has been successful, the content of .ber
is saved in a 2D array which represents a coordinate system. */
void	ft_define_map_size(char *file, t_struct *so_long)
{
	char	*line;
	int		fd;
	int		temp;

	temp = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nFile could not be read.\n", 1);
		close(fd);
		exit(0);
	}
	line = get_next_line(fd);
	so_long->game.map_width = ft_strlen(line) - 1;
	while (line != NULL)
	{
		free(line);
		line = NULL;
		so_long->game.map_height++;
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	ft_allocate_map_memory(so_long);
	ft_read_map_grid(file, so_long);
}
