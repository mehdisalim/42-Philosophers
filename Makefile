# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esalim <esalim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 20:13:51 by esalim            #+#    #+#              #
#    Updated: 2023/03/06 20:28:38 by esalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -g

SRCS	=	main.c

OBJS	=	${SRCS:.c=.o}

RM		=	rm -rf

all		:	$(NAME)

$(NAME)	:	$(OBJS)

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^

clean	:
	$(RM)	$(OBJS)

fclean	:	clean
	$(RM) $(NAME)

re		: fclean all