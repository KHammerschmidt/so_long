/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khammers <khammers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 10:24:39 by khammers          #+#    #+#             */
/*   Updated: 2021/10/19 16:15:20 by khammers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* Check for 2 command line arguments, the last one of .ber format. Return 0 if
input is correct, print an error message and return -1 if not. */
int	ft_handle_input(int argc, char **argv)
{
	char	*map_format;

	map_format = ".ber";
	if (argv[1] == NULL || argc != 2)
	{
		ft_putstr_fd("Error\nNo valid map.\n", 1);
		return (-1);
	}
	if (!ft_strncmp((argv[1] - 4), map_format, 4))
	{
		ft_putstr_fd("Error\nNo valid map in .ber format.\n", 1);
		return (-1);
	}
	return (0);
}
