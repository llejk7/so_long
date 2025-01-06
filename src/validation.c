/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:44:56 by krenken           #+#    #+#             */
/*   Updated: 2025/01/06 15:42:49 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Validates paths in the map
int	validate_paths(t_game *game)
{
	char	**map_copy;
	int		result;

	map_copy = copy_map(game->map, game->map_height);
	if (!map_copy)
		return (0);
	result = start_flood_fill(game, map_copy);
	free_map(map_copy);
	return (result);
}

// Validates the walls surrounding the map
int	validate_walls(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map_width)
	{
		if (game->map[0][i] != '1' || game->map[game->map_height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < game->map_height)
	{
		if (game->map[i][0] != '1' || game->map[i][game->map_width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

// Validates the entire map
int	validate_map(t_game *game)
{
	if (!game->map || game->map_width == 0 || game->map_height == 0)
		return (0);
	if (!has_valid_characters(game))
		return (0);
	if (!validate_walls(game))
		return (0);
	if (!validate_paths(game))
		return (0);
	return (1);
}

int	has_valid_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!is_valid_character(game->map[i][j]))
				return (0);
			update_counts(game, game->map[i][j], j, i);
			j++;
		}
		i++;
	}
	return (game->player == 1 && game->exits >= 1 && game->collectibles >= 1);
}
