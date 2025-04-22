# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anonymous <anonymous@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 12:00:00 by anonymous         #+#    #+#              #
#    Updated: 2025/04/22 12:00:00 by anonymous        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Compiler flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lreadline

# Source files
SRC_DIR = srcs
SRCS = $(SRC_DIR)/main.c \
	   $(SRC_DIR)/execute_cmd.c \
	   $(SRC_DIR)/execute_pipeline.c \
	   $(SRC_DIR)/redirections.c \
	   $(SRC_DIR)/builtins.c \
	   $(SRC_DIR)/builtin_echo.c \
	   $(SRC_DIR)/builtin_cd.c \
	   $(SRC_DIR)/builtin_pwd.c \
	   $(SRC_DIR)/builtin_export.c \
	   $(SRC_DIR)/builtin_unset.c \
	   $(SRC_DIR)/builtin_env.c \
	   $(SRC_DIR)/builtin_exit.c \
	   $(SRC_DIR)/env_utils.c \
	   $(SRC_DIR)/env_utils2.c \
	   $(SRC_DIR)/env_utils3.c \
	   $(SRC_DIR)/expansion.c \
	   $(SRC_DIR)/utils.c \
	   $(SRC_DIR)/utils2.c \
	   $(SRC_DIR)/signals.c \
	   $(SRC_DIR)/parser.c \
	   $(SRC_DIR)/tokenizer.c \
	   $(SRC_DIR)/cmd_list.c \
	   $(SRC_DIR)/init.c

# Object files
OBJ_DIR = objs
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft
LIBFT = libft/libft.a
LIBFT_DIR = libft

# Header files
INCLUDES = -I includes -I $(LIBFT_DIR)

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) successfully created!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)Cleaning binaries...$(RESET)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
