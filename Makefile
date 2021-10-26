# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlebard <mlebard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/27 17:27:08 by mlebard           #+#    #+#              #
#    Updated: 2021/10/19 23:51:15 by mlebard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		:=	/bin/zsh

# NAME
NAME		=	philo

# DIR
S_DIR		=	srcs/
S_BONUS_DIR	=	bonus/
BIN_DIR		=	bin/
O_DIR		=	bin/obj/

# COLORS
YLW			=	\033[1;33m# Yellow
GRN			=	\033[1;32m# Green
WHT			=	\033[1;37m# White
RED			=	\033[1;31m
BLU			=	\033[1;34m
NC			=	\033[0m# No Color

OW			=	\r\033[1A\033[K# OverWrite previous line
OW2			=	\r\033[2A\033[K# OverWrite previous 2 lines
OW3			=	\r\033[3A\033[K# OverWrite previous 3 lines

# COMPILE
CC				=	gcc
CFLAGS			=	-Werror -Wextra -Wall -Iinclude -pthread -g3
LDFLAGS			= 	-pthread
LEAKS			=	-fsanitize=address

# SRCS
SOURCES		=	main.c \
				parse.c \
				init_free.c \
				life.c \
				death.c \
				forks.c \
				utils.c \
				libft_utils.c
SRCS		=	$(addprefix $(S_DIR),$(SOURCES))

# OBJS
OBJECTS		=	$(SOURCES:.c=.o)
OBJS		=	$(addprefix $(O_DIR),$(OBJECTS))

all				:
				@echo "$(WHT)\033[4mBuilding $(NAME):\033[0m$(NC)"
				@make --no-print-directory $(NAME)

$(NAME)			:	$(OBJS)
				@echo -n "\n$(OW)$(YLW)Linking $(NAME)...$(NC)"
				@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
				@echo "\n$(OW)$(GRN)$(NAME) built successfully!$(NC)"

$(OBJS)			:	$(O_DIR)%.o: $(S_DIR)%.c
				@echo -n "\n$(OW)$(YLW)Compiling $<$(NC)"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

norm			:
				@echo "$(BLU)$(NAME): Checking norm for all source and header files$(NC)"
				@norminette $(SRCS)

clean			:
				@echo "$(BLU)$(NAME): cleaning objs$(NC)"
				rm -r -f $(BIN_DIR)

fclean			:	clean
				@echo "$(BLU)$(NAME): cleaning binary$(NC)"
				rm -r -f $(NAME)

re				:	fclean all

.PHONY			:	all libft bonus sanitize san_bonus norm clean fclean allclean re
