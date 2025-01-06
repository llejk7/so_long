/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:44:56 by krenken           #+#    #+#             */
/*   Updated: 2025/01/06 14:46:01 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void flood_fill(char **map, int x, int y, int *collectibles_found, int *exit_found)
{
    if (map[y][x] == '1' || map[y][x] == 'F')
        return;
    if (map[y][x] == 'C')
        (*collectibles_found)++;
    if (map[y][x] == 'E')
        (*exit_found)++;
    map[y][x] = 'F';
    flood_fill(map, x + 1, y, collectibles_found, exit_found);
    flood_fill(map, x - 1, y, collectibles_found, exit_found);
    flood_fill(map, x, y + 1, collectibles_found, exit_found);
    flood_fill(map, x, y - 1, collectibles_found, exit_found);
}

static int run_flood_fill(t_game *game, char **map_copy)
{
    int i;
    int j;
    int collectibles_found;
    int exit_found;

    collectibles_found = 0;
    exit_found = 0;
    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == 'P')
            {
                flood_fill(map_copy, j, i, &collectibles_found, &exit_found);
                return (collectibles_found == game->collectibles &&
                        exit_found == game->exits);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int validate_paths(t_game *game)
{
    char **map_copy;
    int result;

    map_copy = copy_map(game->map, game->map_height);
    if (!map_copy)
        return (0);
    result = run_flood_fill(game, map_copy);
    free_map(map_copy);
    return (result);
}

int validate_walls(t_game *game)
{
    int i;

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

int validate_map(t_game *game)
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

int has_valid_characters(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->map[i])
    {
        j = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] != '0' && game->map[i][j] != '1' &&
                game->map[i][j] != 'C' && game->map[i][j] != 'E' &&
                game->map[i][j] != 'P')
                return (0);
            if (game->map[i][j] == 'C')
                game->collectibles++;
            else if (game->map[i][j] == 'E')
                game->exits++;
            else if (game->map[i][j] == 'P')
            {
                game->player++;
                game->player_x = j;
                game->player_y = i;
            }
            j++;
        }
        i++;
    }
    if (game->player != 1 || game->exits < 1 || game->collectibles < 1)
        return (0);
    return (1);
}
