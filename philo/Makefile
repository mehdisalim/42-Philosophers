# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esalim <esalim@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 20:13:51 by esalim            #+#    #+#              #
#    Updated: 2023/03/22 10:01:27 by esalim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC	=	cc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=thread

SRCS	=	main.c times.c philo_utils.c threads.c activities.c check_args.c

OBJS	=	${SRCS:.c=.o}

RM		=	rm -rf

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CC) $(CFLAGS) $^ -o $@  -lpthread

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^

clean	:
	$(RM)	$(OBJS)

fclean	:	clean
	$(RM) $(NAME)

re		: fclean all