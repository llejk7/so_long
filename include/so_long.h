/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krenken <krenken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:00:04 by krenken           #+#    #+#             */
/*   Updated: 2025/01/06 15:47:01 by krenken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../minilibx-linux/mlx.h"

// Constants
# define TILE_SIZE 64

// Game structure
typedef struct s_game
{
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		exits;
	int		player;
	int		steps;

	// MiniLibX resources
	void	*mlx;
	void	*window;
	void	*wall_image;
	void	*floor_image;
	void	*player_image;
	void	*collectible_image;
	void	*exit_image;
}	t_game;

// Flood fill parameters
typedef struct s_fill_params
{
	int	*collectibles_found;
	int	*exit_found;
}	t_fill_params;

// Core map parsing
char	**parse_map(const char *file, t_game *game);
void	free_map(char **map);
char	**copy_map(char **map, int height);

// Validation
int		validate_map(t_game *game);
int		validate_paths(t_game *game);
int		validate_walls(t_game *game);
int		has_valid_characters(t_game *game);
int		is_valid_character(char c);
void	update_counts(t_game *game, char c, int x, int y);
void	flood_fill(char **map, int x, int y, t_fill_params *params);
int		start_flood_fill(t_game *game, char **map_copy);

// Rendering
void	render_map(t_game *game);
void	render_tile(t_game *game, char tile, int x, int y);
void	load_images(t_game *game);

// Event handling
int		handle_keypress(int keycode, t_game *game);
int		handle_close(t_game *game);
void	move_player(t_game *game, int dx, int dy);

// Cleanup
void	cleanup_and_exit(t_game *game, const char *error_message);

#endif
