/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 23:14:40 by krenken           #+#    #+#             */
/*   Updated: 2024/12/21 00:18:59 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <unistd.h> // For write
#include <stdlib.h> // For exit

static void	print_map(char **map);

int	main(int argc, char **argv)
{
	char	**map;

	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 28);
		return (1);
	}
	map = read_map(argv[1]);
	if (!map)
		return (1);
	print_map(map);
	free_map(map, 0); // Free map; pass 0 because the map is NULL-terminated
	return (0);
}

static void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		write(1, map[i], ft_strlen(map[i])); // Assume you have ft_strlen
		write(1, "\n", 1);
		i++;
	}
}
