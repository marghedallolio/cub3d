# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdalloli <mdalloli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/29 14:09:53 by mdalloli          #+#    #+#              #
#    Updated: 2025/10/29 14:24:11 by mdalloli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME = cub3d
LIBFT = libft/libft.a

CC = cc
CFLAGS = -Werror -Wextra -Wall

SRC = main.c
PARSING_SRC = parse_color.c parse_file.c parse_line.c parse_map.c parse_utils.c

OBJ = $(SRC:.c=.o)
PARSING_OBJ = $(addprefix signals/, $(PARSING_SRC:.c=.o))

ALL_OBJS = $(OBJ) $(PARSING_OBJ)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

$(NAME): $(ALL_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $^

clean:
	rm -f $(ALL_OBJS)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re