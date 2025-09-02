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
NAME		= philo

# Compiler and Flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I. #-fsanitize=thread

# Threading flags
THREAD_FLAGS = -pthread

# Sources and Objects
SRCS		= $(wildcard *.c)
OBJS		= $(SRCS:.c=.o)

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

$(NAME): $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) $(THREAD_FLAGS) -o $(NAME)
	@clear
	@echo "$$ART"
	@echo "$(CYAN)Philosophers compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@sleep 0.02
	@clear
	@echo "$(RED)Compiling philosophers sources $<$(RESET)"

clean:
	@clear
	@rm -rf ./*.o
	@echo "$(YELLOW)Object files cleaned!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(YELLOW)Executable removed!$(RESET)"

re: fclean $(NAME)

.PHONY: all clean fclean re
