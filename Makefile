# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 14:09:53 by mdalloli          #+#    #+#              #
#    Updated: 2025/12/04 16:41:28 by mdalloli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -g

MLXDIR = mlx
MLX = $(MLXDIR)/libmlx.a
LIBFT = libft/libft.a
MLXFLAGS = -Lmlx -lXext -lm -lmlx -lX11

SRC = main.c dda.c free_close.c
PARSING = extraction_file_info_utils.c extraction_file_info.c file_reading_and_parsing.c \
		parse_map_utils.c parse_map.c pre_parsing_file.c parse_texture.c utils.c
INITS = init_game.c init_vectors.c
DRAWING = drawing.c drawing_utils.c
MOVEMENT = movement.c handle_keys.c

SRC += $(addprefix parsing/, $(PARSING)) $(addprefix inits/, $(INITS)) $(addprefix drawing/, $(DRAWING)) $(addprefix movement/, $(MOVEMENT)) 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(MLX):
	make -C $(MLXDIR)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) -o $(NAME) $(MLXFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re

