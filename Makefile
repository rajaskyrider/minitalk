# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 18:53:31 by rpandipe          #+#    #+#              #
#    Updated: 2024/04/21 20:51:28 by rpandipe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = server client
BONUS = server_bonus client_bonus
SRCS = client.c server.c
SRCB = client_bonus.c server_bonus.c
OBJS = $(SRCS:.c=.o)
OBJB = $(SRCB:.c=.o)
RM = rm -rf

all: $(NAME)

bonus: $(BONUS)

server: server.c
	$(CC) $(CFLAGS) server.c -o server

client: client.c
	$(CC) $(CFLAGS) client.c -o client

server_bonus: server_bonus.c
	$(CC) $(CFLAGS) server_bonus.c -o server

client_bonus: client_bonus.c
	$(CC) $(CFLAGS) client_bonus.c -o client

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJB)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re