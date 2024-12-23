/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 00:12:48 by krenken           #+#    #+#             */
/*   Updated: 2024/12/21 00:13:03 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static char	*ft_strdup(const char *s);
static char	**resize_map(char **map, int rows);
static void	free_line_array(char **map, int rows);

char	**read_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**map;
	int		rows;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), NULL);
	map = NULL;
	rows = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		map = resize_map(map, rows);
		if (!map)
			return (free(line), close(fd), NULL);
		map[rows] = ft_strdup(line);
		free(line);
		if (!map[rows])
			return (free_line_array(map, rows), close(fd), NULL);
		rows++;
	}
	close(fd);
	return (map);
}

static char	**resize_map(char **map, int rows)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (rows + 2));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[rows + 1] = NULL;
	free(map);
	return (new_map);
}

static void	free_line_array(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}
