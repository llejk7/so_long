# Variables
NAME        = so_long
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
MLX_PATH    = minilibx-linux
MLX         = $(MLX_PATH)/libmlx.a
MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm
SRCS        = src/main.c src/map.c src/game.c src/graphics.c src/map_utils.c src/validation.c src/validation_utils.c
OBJS        = $(SRCS:.c=.o)
LIBFT_PATH  = libft
LIBFT       = $(LIBFT_PATH)/libft.a
INCLUDES    = -I include -I $(MLX_PATH) -I $(LIBFT_PATH)

# Colors for better readability
RESET       = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@echo "$(CYAN)Compiling $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT):
	@echo "$(CYAN)Compiling libft...$(RESET)"
	make -C $(LIBFT_PATH)

$(MLX):
	@echo "$(CYAN)Compiling MiniLibX...$(RESET)"
	make -C $(MLX_PATH)

%.o: %.c
	@echo "$(CYAN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	rm -f $(OBJS)
	make clean -C $(MLX_PATH)
	make clean -C $(LIBFT_PATH)

fclean: clean
	@echo "$(CYAN)Removing $(NAME)...$(RESET)"
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)

re: fclean all

# Optional quality-of-life rule
.PHONY: all clean fclean re