# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snagat <snagat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 12:31:51 by snagat            #+#    #+#              #
#    Updated: 2022/06/05 13:47:24 by snagat           ###   ########.fr        #
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
DBGUTILS= $(addprefix dbg_utils/, token_str.c check_lists.c tree_debug.c)
UTILS= $(addprefix utils/, ft_new_node.c node_operations_parse.c get_token.c get_cmd.c free_list.c\
		general_utils.c)
LEXERC=$(addprefix lexer/, lexing.c)
PARSERC=$(addprefix parser/, pipe.c handle_single_quotes.c handle_double_quotes.c)
CFILES= $(addprefix src/, $(LEXERC) $(MAIN) $(UTILS) $(DBGUTILS) $(PARSERC))
OFILES=$(addprefix build/, $(CFILES:.c=.o))
LIBFT=libft/libft.a
PROGRAM= minishell

all: $(PROGRAM)

$(PROGRAM) : $(OFILES)
	@cd libft && make
	$(CC) $(FLAGS) $(LDFLAGS) $(CPPFLAGS) -g -lreadline $(OFILES) $(LIBFT) -I $(INC) -o $(PROGRAM)
	
$(B_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(CPPFLAGS) -I $(INC) -c $< -o $@

clean:
	rm -rf $(B_DIR)
	@cd libft && make fclean

fclean: clean
	rm  -f $(PROGRAM)

re: fclean all