# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snagat <snagat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/04 01:25:13 by snagat            #+#    #+#              #
#    Updated: 2021/12/04 01:43:33 by snagat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
FLAGS=-Wall -Wextra -Werror
AR=ar crs
RM=rm -rf
FILEC= ft_printf ft_putchar ft_putnbr ft_cnvert_hex ft_putnbr_uns ft_putstr
FILES= $(addprefix src/, $(FILEC))
SRC=$(FILES:=.c)
OBJ=$(FILES:=.o)
INC=inc/
HDR= $(addprefix inc/, ft_printf.h);
NAME=libftprintf.a

.PHONY:all clean fclean re bonus

all:$(NAME)

$(NAME):$(OBJ)
	$(AR) $(NAME)  $(OBJ)
%.o : %.c $(HDR)
	$(CC) $(FLAGS) -I $(INC) -c $< -o $@
clean:
	$(RM) $(OBJ)
fclean : clean
	$(RM) $(NAME)

re : fclean all