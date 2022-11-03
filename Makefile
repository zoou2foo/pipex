# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valeriejean <valeriejean@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 16:41:48 by vjean             #+#    #+#              #
#    Updated: 2022/11/03 08:08:03 by valeriejean      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c parsing.c \

LIBFT =	libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS = -g -Wall -Wextra -Werror

.c.o:
		@$(CC)$(CFLAGS) -c $< -o $(<:.c=.o)

#AR = ar rcs

RM = rm -fr

all: $(NAME)

$(NAME): $(OBJS)
	cd libft && make
		@$(CC) $(OBJS) $(LIBFT) -o $(NAME)
exec: re $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	
re: fclean all

.PHONY: all clean fclean re