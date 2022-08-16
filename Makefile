# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snagat <snagat@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 12:31:51 by snagat            #+#    #+#              #
#    Updated: 2022/08/14 19:52:29 by snagat           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#FIXME: We should add checks on the headers too.
CC=gcc
INC=inc/
FLAGS=-Wall -Wextra -Werror
MAIN=main.c
B_DIR= build
# If a new directory is created inside src, we should have it in a variable
# containing all files inside, and add it to CFILES too.
DBGUTILS= $(addprefix dbg_utils/, token_str.c check_lists.c tree_debug.c visual_tree.c)
UTILS= $(addprefix utils/, ft_new_node.c node_operations_parse.c get_token.c get_cmd.c free_list.c\
		general_utils.c number_utils.c free_tree.c)
LEXERC=$(addprefix lexer/, lexing.c)
PARSERC=$(addprefix parser/, parser.c)
PARSETREE=$(addprefix parser/main_tree/, main_tree.c analyze_cmd.c)
PARSEPIPE=$(addprefix parser/pipe/, pipe.c)
PARSQUOTES = $(addprefix parser/quotes/, handle_single_quotes.c handle_double_quotes.c handle_quotes.c)
PARSCHECK= $(addprefix parser/checks/, check_quotes.c check_all.c two_nearby_tokens.c check_conditional.c check_paranthesis.c) 
PARSRED= $(addprefix parser/redirections/, o_redr.c)
PARSENV= $(addprefix parser/expansion/, expand.c wildcard.c)
PARSEP=$(addprefix parser/parenthesis/, parse_parenthesis.c)
EXEC=$(addprefix exec/, exec.c gen_utils.c error_handling.c reds_exec.c or_and_exec.c)
BUILTINS= $(addprefix exec/builtins/, check_builtins.c echo.c cd.c pwd.c env.c copy_env.c cd_utils.c exit.c ft_unset.c export.c export_utils.c)
CFILES= $(addprefix src/, $(LEXERC) $(MAIN) $(UTILS) $(DBGUTILS) $(PARSCHECK) $(PARSEPIPE) $(PARSQUOTES) $(PARSRED) $(PARSENV) $(PARSETREE) $(PARSEP) $(PARSERC) $(EXEC) $(BUILTINS))
OFILES=$(addprefix build/, $(CFILES:.c=.o))
LIBFT=libft/libft.a
PROGRAM= minishell

all: $(PROGRAM)

$(PROGRAM) : $(OFILES)
	@cd libft && make
	$(CC) $(FLAGS) $(LDFLAGS) $(CPPFLAGS) -g  $(OFILES) $(LIBFT) -I $(INC) -o $(PROGRAM) -lreadline
	
$(B_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) $(CPPFLAGS) -I $(INC) -g -c $< -o $@

clean:
	rm -rf $(B_DIR)
	@cd libft && make fclean

fclean: clean
	rm  -f $(PROGRAM)

re: fclean all
