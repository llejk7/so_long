/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:04:02 by kjell             #+#    #+#             */
/*   Updated: 2025/01/05 15:17:09 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	render_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			render_tile(game, game->map[i][j], j, i);
			j++;
		}
		i++;
	}
}

void	render_tile(t_game *game, char tile, int x, int y)
{
	void	*image;

	if (tile == '1')
		image = game->wall_image;
	else if (tile == '0')
		image = game->floor_image;
	else if (tile == 'P')
		image = game->player_image;
	else if (tile == 'C')
		image = game->collectible_image;
	else if (tile == 'E')
		image = game->exit_image;
	else
		return ;
	mlx_put_image_to_window(
		game->mlx, game->window, image, x * TILE_SIZE, y * TILE_SIZE);
}

void	load_images(t_game *game)
{
	int	img_width;
	int	img_height;

	game->wall_image = mlx_xpm_file_to_image(
			game->mlx, "textures/wall.xpm", &img_width, &img_height);
	game->floor_image = mlx_xpm_file_to_image(
			game->mlx, "textures/floor.xpm", &img_width, &img_height);
	game->player_image = mlx_xpm_file_to_image(
			game->mlx, "textures/player.xpm", &img_width, &img_height);
	game->collectible_image = mlx_xpm_file_to_image(
			game->mlx, "textures/collectible.xpm", &img_width, &img_height);
	game->exit_image = mlx_xpm_file_to_image(
			game->mlx, "textures/exit.xpm", &img_width, &img_height);
	if (!game->wall_image || !game->floor_image
		|| !game->player_image || !game->collectible_image
		|| !game->exit_image)
	{
		cleanup_and_exit(game, "Error: Failed to load images\n");
	}
}
