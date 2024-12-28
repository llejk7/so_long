# Variables
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLX_PATH = minilibx-linux
MLX = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
SRCS = src/main.c src/map.c src/game.c src/graphics.c
OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a
INCLUDES = -I include -I $(MLX_PATH) -I libft

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C libft

$(MLX):
	make -C $(MLX_PATH)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(MLX_PATH)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
