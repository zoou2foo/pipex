# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vjean <vjean@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/01 16:41:48 by vjean             #+#    #+#              #
#    Updated: 2022/11/29 13:02:15 by vjean            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus

SRCS = srcs/main.c \
	srcs/pipex.c srcs/utils.c srcs/work_in_processes.c srcs/free_stuff.c \

BONUS = bonus/pipex_bonus.c bonus/utils_bonus.c bonus/free_stuff_bonus.c \
	bonus/main_bonus.c bonus/work_in_processes_bonus.c \

LIBFT =	libft/libft.a

OBJS = $(SRCS:.c=.o)

CC = gcc 

CFLAGS = -g -Wall -Wextra -Werror

BONUS_OBJS = $(BONUS:.c=.o)

#*****INTRO*****
define intro
@bash pew_pew.sh
endef

.c.o:
		@$(CC)$(CFLAGS) -I includes -c $< -o $(<:.c=.o)

RM = rm -fr

all: $(NAME)

$(NAME): $(OBJS)
	$(call intro)
	cd libft && make
		@$(CC) -I includes $(OBJS) $(LIBFT)  -o $(NAME)
		
exec: re $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex

clean:
	$(RM) $(OBJS)
	$(RM) $(BONUS_OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	
re: fclean all

bonus: $(BONUS_OBJS)
	$(call intro)
	cd libft && make
		@$(CC) -I includes $(BONUS_OBJS) $(LIBFT) -o $(NAME_BONUS)

.PHONY: all clean fclean re