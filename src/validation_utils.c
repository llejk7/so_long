/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 15:32:24 by krenken           #+#    #+#             */
/*   Updated: 2025/01/06 15:43:09 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

// Checks if a character is valid
int	is_valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}

// Updates game counts for collectibles, exits, and player
void	update_counts(t_game *game, char c, int x, int y)
{
	if (c == 'C')
		game->collectibles++;
	else if (c == 'E')
		game->exits++;
	else if (c == 'P')
	{
		game->player++;
		game->player_x = x;
		game->player_y = y;
	}
}

// Flood fill function for path validation
void	flood_fill(char **map, int x, int y, t_fill_params *params)
{
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		(*params->collectibles_found)++;
	if (map[y][x] == 'E')
		(*params->exit_found)++;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, params);
	flood_fill(map, x - 1, y, params);
	flood_fill(map, x, y + 1, params);
	flood_fill(map, x, y - 1, params);
}

// Initiates flood fill for path validation
int	start_flood_fill(t_game *game, char **map_copy)
{
	int				i;
	int				j;
	t_fill_params	params;

	params.collectibles_found = &(int){0};
	params.exit_found = &(int){0};
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				flood_fill(map_copy, j, i, &params);
				return ((*params.collectibles_found == game->collectibles)
					&& (*params.exit_found == game->exits));
			}
			j++;
		}
		i++;
	}
	return (0);
}
