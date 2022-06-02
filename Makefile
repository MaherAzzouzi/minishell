# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snagat <snagat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 12:31:51 by snagat            #+#    #+#              #
#    Updated: 2022/06/02 10:54:37 by snagat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FIXME: We should add checks on the headers too.
CC=cc
INC=inc/
FLAGS=-Wall -Wextra -Werror
MAIN=main.c
B_DIR= build
# If a new directory is created inside src, we should have it in a variable
# containing all files inside, and add it to CFILES too.
TMPUTS= $(addprefix tmp_utils/, token_str.c check_lists.c)
UTILS= $(addprefix utils/, ft_new_node.c node_operations_parse.c)
LEXERC=$(addprefix lexer/, lexing.c)
PARSERC=$(addprefix parser/, pipe.c)
CFILES= $(addprefix src/, $(LEXERC) $(MAIN) $(UTILS) $(TMPUTS) $(PARSERC))
OFILES=$(addprefix build/, $(CFILES:.c=.o))
LIBFT=libft/libft.a
PROGRAM= minishell

all: $(PROGRAM)

$(PROGRAM) : $(OFILES)
	@cd libft && make
	$(CC) $(FLAGS) $(LDFLAGS) $(CPPFLAGS) -lreadline $(OFILES) $(LIBFT) -I $(INC) -o $(PROGRAM)
	
$(B_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -I $(INC) -c $< -o $@

clean:
	rm -rf $(B_DIR)
	@cd libft && make fclean

fclean: clean
	rm  -f $(PROGRAM)

re: fclean all