# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 14:09:53 by mdalloli          #+#    #+#              #
#    Updated: 2025/10/30 14:57:22 by mdalloli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cub3d
LIBFT = libft/libft.a
MLX = mlx/libmlx.a
DIR_MLX = mlx/

CC = cc
CFLAGS = -Werror -Wextra -Wall
MLXFLAGS = -Lmlx -lXext -lm -lmlx -lX11

SRC = main.c
PARSING_SRC = parse_color.c parse_file.c parse_line.c parse_map.c parse_utils.c

OBJ = $(SRC:.c=.o)
PARSING_OBJ = $(addprefix parsing/, $(PARSING_SRC:.c=.o))

ALL_OBJS = $(OBJ) $(PARSING_OBJ)

all: $(NAME)

$(MLX):
	make -C $(DIR_MLX)

$(LIBFT):
	make -C libft

$(NAME): $(ALL_OBJS) $(MLX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) -o $(NAME) $(MLXFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(ALL_OBJS)
	make clean -C libft
	make clean -C $(DIR_MLX)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re