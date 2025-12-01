# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 14:09:53 by mdalloli          #+#    #+#              #
#    Updated: 2025/12/01 16:21:59 by francema         ###   ########.fr        #
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

SRC = main.c errors.c init_game.c
PARSING_SRC = parsing/file_info_extr_utils.c parsing/file_info_extr.c \
			parsing/file_reading_and_parsing.c parsing/map_parse_utils.c parsing/map_parse.c\
			parsing/pre_file_parsing.c parsing/texture_parse.c

# RENDERING_SRC = rendering/render_game.c rendering/render_line.c
# RAYCASTING_SRC = raycasting/raycasting_utils.c raycasting/raycasting.c


SRC_ALL = $(SRC) $(PARSING_SRC) #$(RENDERING_SRC) $(RAYCASTING_SRC)
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
