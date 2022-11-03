# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjean <vjean@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 16:41:48 by vjean             #+#    #+#              #
#    Updated: 2022/11/03 15:16:17 by vjean            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS = pipex.c parsing.c \

LIBFT =	libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS = -g -Wall -Wextra -Werror

#*****INTRO*****
define intro
@bash pew_pew.sh
endef

.c.o:
		@$(CC)$(CFLAGS) -c $< -o $(<:.c=.o)

#AR = ar rcs

RM = rm -fr

all: $(NAME)

$(NAME): $(OBJS)
	$(call intro)
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