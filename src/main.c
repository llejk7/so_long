/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjell <kjell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:40:07 by kjell             #+#    #+#             */
/*   Updated: 2024/12/28 20:06:24 by kjell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void free_images(t_game *game)
{
    if (game->wall_image)
        mlx_destroy_image(game->mlx, game->wall_image);
    if (game->floor_image)
        mlx_destroy_image(game->mlx, game->floor_image);
    if (game->player_image)
        mlx_destroy_image(game->mlx, game->player_image);
    if (game->collectible_image)
        mlx_destroy_image(game->mlx, game->collectible_image);
    if (game->exit_image)
        mlx_destroy_image(game->mlx, game->exit_image);
}

void cleanup_and_exit(t_game *game, const char *err_msg)
{
    if (err_msg)
        ft_putstr_fd((char *)err_msg, 2);
    if (game->map)
        free_map(game->map);
    if (game->mlx && game->window)
        mlx_destroy_window(game->mlx, game->window);
    free_images(game);
    exit(err_msg ? 1 : 0);
}

int handle_close(t_game *game)
{
    cleanup_and_exit(game, NULL);
    return (0);
}

static void initialize_game(t_game *game, char **argv)
{
    ft_memset(game, 0, sizeof(t_game));
    game->map = parse_map(argv[1], game);
    if (!game->map || !validate_map(game))
        cleanup_and_exit(game, "Error\nInvalid map\n");
    game->mlx = mlx_init();
    if (!game->mlx)
        cleanup_and_exit(game, "Error\nFailed to initialize graphics\n");
    game->window = mlx_new_window(game->mlx, game->map_width * TILE_SIZE,
                                  game->map_height * TILE_SIZE, "so_long");
    if (!game->window)
        cleanup_and_exit(game, "Error\nFailed to create game window\n");
    load_images(game);
    render_map(game);
}

int main(int argc, char **argv)
{
    t_game game;

    if (argc != 2)
    {
        ft_putstr_fd("Error\nUsage: ./so_long <map_file.ber>\n", 2);
        return (1);
    }
    initialize_game(&game, argv);
    mlx_hook(game.window, 2, 1L << 0, handle_keypress, &game);
    mlx_hook(game.window, 17, 0, handle_close, &game);
    mlx_loop(game.mlx);
    cleanup_and_exit(&game, NULL);
    return (0);
}
