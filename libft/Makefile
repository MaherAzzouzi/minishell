CC=gcc
FLAGS=-Wall -Wextra -Werror
MANDATORY=ft_bzero ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
		  ft_memcpy ft_memmove ft_memset ft_strlcat ft_strlcpy ft_strlen \
		  ft_toupper ft_tolower ft_strchr ft_strrchr ft_memchr ft_strncmp \
		  ft_memcmp ft_atoi ft_calloc ft_strnstr ft_strdup ft_strtrim \
		  ft_substr ft_strjoin ft_split ft_strmapi ft_striteri ft_putchar_fd \
		  ft_putstr_fd ft_putendl_fd ft_putnbr_fd ft_itoa ft_strcmp
BONUS=ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back \
	  ft_lstdelone ft_lstclear ft_lstiter ft_lstmap
BNS_SRCS=$(BONUS:=.c)
BNS_OBJS=$(BONUS:=.o)
SRCS=$(MANDATORY:=.c)
OBJS=$(MANDATORY:=.o)
NAME=libft.a
AR=ar rcs

.PHONY: all clean fclean bonus re

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

bonus: all $(BNS_OBJS)
	@$(AR) $(NAME) $(BNS_OBJS)

%.o: %.c libft.h
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@rm -f $(BNS_OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
