# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 14:09:53 by mdalloli          #+#    #+#              #
#    Updated: 2025/11/20 18:29:15 by mdalloli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cube3d
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
DIR_MLX = mlx/

CC = cc
CFLAGS = -Werror -Wextra -Wall -g
MLXFLAGS = -Lmlx -lXext -lm -lmlx -lX11

SRC = main.c errors.c init.c
PARSING_SRC = parsing/parse_color.c parsing/parse_file.c parsing/parse_line.c parsing/parse_map.c parsing/parse_utils.c parsing/parse_map_utils.c
RENDERING_SRC = rendering/render_game.c rendering/render_line.c
RAYCASTING_SRC = raycasting/raycasting_utils.c raycasting/raycasting.c


SRC_ALL = $(SRC) $(PARSING_SRC) $(RENDERING_SRC) $(RAYCASTING_SRC)
OBJ = $(SRC_ALL:.c=.o)

all: $(NAME)

$(MLX):
	make -C $(DIR_MLX)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) -o $(NAME) $(MLXFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C libft
	make clean -C $(DIR_MLX)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
