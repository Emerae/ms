CC			= clang -Wall -Wextra -Werror
RM			= rm -rf
NAME		= minishell 
INCS_DIR	= ./includes/
MAIN_INC	= -I$(INCS_DIR)

#LIB_DIR		= ./libft/
#LIB_INC		= -I$(LIB_DIR)includes/
#LIB_NAME	= $(LIB_DIR)libft.a
LIB_NAME	= libft.a

INCS		= $(addprefix $(INCS_DIR), minishell.h structures.h)

SRCS		=  $(addprefix sources/, \
			main.c )
 
OBJS		= $(SRCS:.c=.o)

%.o			: %.c
			@$(CC) $(MAIN_INC) $(LIB_INC) -c $< -o $@

all			: $(NAME)

$(NAME)		: $(OBJS) $(INCS)
			@make --silent -C $(LIB_DIR)
#			@$(CC) $(OBJS) $(LIB_NAME) -L$(LIB_DIR) $(LIB_INC) $(MAIN_INC) -o $(NAME)
			@$(CC) $(OBJS) $(LIB_NAME) $(MAIN_INC) -o $(NAME)
			@echo "minishell compiled"

clean:
			@$(MAKE) clean --silent -C $(LIB_DIR)
			@$(RM) $(OBJS)

fclean		: clean
			@$(MAKE) fclean --silent -C $(LIB_DIR)
			@$(RM) $(NAME)

re			: fclean all

.PHONY		: all clean fclean re
