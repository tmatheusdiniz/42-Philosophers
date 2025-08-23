# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreinald <mreinald@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/15 22:06:17 by mreinald          #+#    #+#              #
#    Updated: 2025/08/15 22:06:30 by mreinald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RED		= \033[0;31m
GREEN	= \033[0;32m
BLUE	= \033[0;34m
D_BLUE	= \033[34m
WHITE	= \033[0;37m
YELLOW	= \033[0;33m
MAGENTA	= \033[0;35m
CYAN	= \033[3;36m
RESET	= \033[0m

# Program's name
NAME		= bin/philo

# Directories
SRC_DIR		= ./srcs
OBJ_DIR		= objs
BIN_DIR		= bin
LIBFT_DIR	=./42-Libft

# Compiler and Flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -Iincludes -I$(LIBFT_DIR)

# Libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft

# Threading flags
THREAD_FLAGS = -pthread

# Sources and Objects
SRCS		= $(wildcard $(SRC_DIR)/*.c)
OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# ASCII Art
define ART
$(MAGENTA) ${D_BLUE}
	██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗
	██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝
	██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗
	██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║
	██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║
	╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝
  $(CYAN)━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━[$(RESET)I never thought philosophy would be so deadly$(CYAN)]━━━━━━━━━━━━━━━━━━━━━━━━━━━━━$(RESET)
endef
export ART

# Rules
all: submodule $(NAME)

submodule:
	@git submodule update --init --recursive

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(INCLUDES) $(LIBFT_FLAGS) $(THREAD_FLAGS) -o $(NAME)
	@clear
	@echo "$$ART"
	@echo "$(CYAN)Philosophers compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@sleep 0.02
	@clear
	@echo "$(RED)Compiling philosophers sources $<$(RESET)"

$(LIBFT):
	@make bonus --silent -C $(LIBFT_DIR)

clean:
	@clear
	@make --silent -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)Object files cleaned!$(RESET)"

fclean: clean
	@make --silent -C $(LIBFT_DIR) clean
	@rm -f $(BIN_DIR)
	@echo "$(YELLOW)Executable removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
