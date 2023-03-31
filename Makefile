# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcloarec <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/24 09:47:34 by mcloarec          #+#    #+#              #
#    Updated: 2022/12/03 14:58:54 by mcloarec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c \
	   srcs/init.c \
	   srcs/check_arg.c \
	   srcs/philosophers.c \
	   srcs/philosophers_utils.c \
	   srcs/utils.c \
	   srcs/free.c \

OBJS = ${SRCS:.c=.o}

NAME = philo

CFLAGS = -Wall -Wextra -Werror -g -pthread

RM = rm -rf

all: ${NAME}

.c.o:
	@clang ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
		@clang ${CFLAGS} ${OBJS} -o ${NAME}
		@echo "philo compilation completed"

clean:
		${RM} ${OBJS}
		@echo "clean done"

fclean: clean
		${RM} ${NAME}
		@echo "fclean done"

re: fclean all

.SILENT:

.PHONY: all clean fclean re
