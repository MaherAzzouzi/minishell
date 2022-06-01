# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snagat <snagat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 12:31:51 by snagat            #+#    #+#              #
#    Updated: 2022/06/01 13:21:36 by snagat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
INC=inc/
FLAGS=-Wall -Wextra -Werror
MAIN=main.c
B_DIR= build
# If a new directory is created inside src, we should have it in a variable
# containing all files inside, and add it to CFILES too.
LEXERC=$(addprefix lexer/, lexing.c)
CFILES= $(addprefix src/, $(LEXERC) $(MAIN))
OFILES=$(addprefix build/, $(CFILES:.c=.o))
PROGRAM= minishell

all: $(PROGRAM)

$(PROGRAM) : $(OFILES)
	$(CC) $(FLAGS) $(LDFLAGS) $(CPPFLAGS) -lreadline $(OFILES) -I $(INC) -o $(PROGRAM)
	
$(B_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -I $(INC) -c $< -o $@

clean:
	rm -rf $(B_DIR)

fclean: clean
	rm  -f $(PROGRAM)

re: fclean all