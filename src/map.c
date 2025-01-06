/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:53:16 by kjell             #+#    #+#             */
/*   Updated: 2025/01/06 15:21:37 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

static char	**allocate_map(int height)
{
	char	**map;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	return (map);
}

static int	fill_map(int fd, char **map, int height)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (i < height && line != NULL)
	{
		map[i] = ft_strtrim(line, "\n");
		free(line);
		if (!map[i])
			return (0);
		i++;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (1);
}

static int	initialize_map(const char *file, t_game *game, char ***map)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	game->map_height = count_lines(fd);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	*map = allocate_map(game->map_height);
	if (!(*map))
	{
		close(fd);
		return (0);
	}
	return (fd);
}

char	**parse_map(const char *file, t_game *game)
{
	char	**map;
	int		fd;

	fd = initialize_map(file, game, &map);
	if (!fd)
		return (NULL);
	if (!fill_map(fd, map, game->map_height))
	{
		free_map(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	game->map_width = ft_strlen(map[0]);
	return (map);
}
