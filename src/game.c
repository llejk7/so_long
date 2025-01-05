/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:04:43 by kjell             #+#    #+#             */
/*   Updated: 2025/01/05 15:11:27 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

#define ESC_KEY 65307
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100

static void	handle_collectible(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
		game->collectibles--;
}

static void	handle_exit(t_game *game)
{
	if (game->collectibles == 0)
	{
		ft_putstr_fd("Game completed!\n", 1);
		cleanup_and_exit(game, NULL);
	}
}

static void	update_player_position(t_game *game, int new_x, int new_y)
{
	game->map[game->player_y][game->player_x] = '0';
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	ft_putstr_fd("Steps: ", 1);
	ft_putnbr_fd(++game->steps, 1);
	ft_putstr_fd("\n", 1);
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (new_x < 0 || new_y < 0 || new_x >= game->map_width
		|| new_y >= game->map_height || game->map[new_y][new_x] == '1')
		return ;
	handle_collectible(game, new_x, new_y);
	if (game->map[new_y][new_x] == 'E')
	{
		handle_exit(game);
		return ;
	}
	update_player_position(game, new_x, new_y);
	render_map(game);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		cleanup_and_exit(game, NULL);
	if (keycode == W_KEY)
		move_player(game, 0, -1);
	else if (keycode == A_KEY)
		move_player(game, -1, 0);
	else if (keycode == S_KEY)
		move_player(game, 0, 1);
	else if (keycode == D_KEY)
		move_player(game, 1, 0);
	return (0);
}
