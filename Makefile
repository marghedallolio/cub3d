# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: francema <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 14:09:53 by mdalloli          #+#    #+#              #
#    Updated: 2025/12/01 17:39:31 by francema         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3d
CC = cc
CFLAGS = -Werror -Wextra -Wall -g

MLXDIR = mlx
MLX = $(MLXDIR)/libmlx.a
LIBFT = libft/libft.a
MLXFLAGS = -Lmlx -lXext -lm -lmlx -lX11

SRC = main.c movement.c dda.c
PARSING = file_info_extr_utils.c file_info_extr.c file_reading_and_parsing.c \
		map_parse_utils.c map_parse.c pre_file_parsing.c texture_parse.c utils.c
INITS = init_game.c init_vectors.c
DRAWING = drawing.c drawing_utils.c

SRC += $(addprefix parsing/, $(PARSING)) $(addprefix inits/, $(INITS)) $(addprefix drawing/, $(DRAWING))

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

