# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvithara <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 20:20:12 by tvithara          #+#    #+#              #
#    Updated: 2025/06/19 20:20:15 by tvithara         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror 

LIBFT_PATH=./libft
LIBFT = $(LIBFT_PATH)/libft.a
LIBFT_FLAG= -L$(LIBFT_PATH) -lft

SRC_SERVER = ./src/server.c
SRC_CLIENT = ./src/client.c 

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

$(NAME_SERVER): $(LIBFT) $(OBJ_SERVER)
		@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAG)
		@echo "$(NAME_CLIENT) OK!"

$(NAME_CLIENT): $(LIBFT) $(OBJ_CLIENT)
		@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_FLAG)
		@echo "$(NAME_CLIENT) OK!"

$(LIBFT):
		@$(MAKE) --no-print-directory -C $(LIBFT_PATH)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME_SERVER) $(NAME_CLIENT)	

clean: 
		@$(RM) $(OBJ_SERVER) $(OBJ_CLIENT)
		@$(MAKE) --no-print-directory -C $(LIBFT_PATH) clean
		@echo "object files removed successfully!"

fclean: clean
	@$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	@$(RM) $(LIBFT)
	@echo "executable files removed successfully!"

re: fclean all

.PHONY: all re clean fclean bonus