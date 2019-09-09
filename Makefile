# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/29 13:33:28 by amansour          #+#    #+#              #
#    Updated: 2019/07/02 09:55:59 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
# SOURCES       															   #
################################################################################

SRCS	= $(addprefix $(PATH_SRCS)/, \
							main.c\
							stdin.c\
							error.c\
							usage.c\
							tools.c)

SRCS_HASH	= $(addprefix $(PATH_HASH)/, \
							check.c\
							md5.c\
							sha256.c\
							sha224.c\
							sha512.c\
							sha384.c\
							sha512256.c\
							sha512224.c\
							print_hash.c\
							treat_digest.c\
							cmd_array.c\
							prepare_hash.c\
							hash_sha2_256.c\
							hash_sha2_512.c)

################################################################################
# BASIC VARIABLES															   #
################################################################################
PATH_SRC = src
C_DIR = $(addprefix $(PATH_SRC)/, \
		src \
		src_hash)

C_FILES = $(addprefix $(PATH_SRC)/, \
		  $(SRCS_HASH) \
		  $(SRCS))
PATH_SRCS	= src_ssl
PATH_HASH	= src_hash
PATH_INC	= inc
O_DIR = $(C_DIR:$(PATH_SRC)/%=$(PATH_OBJ)/%)
O_FILES = $(C_FILES:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)
PATH_OBJ	= obj
NAME		= ft_ssl
CFLAGS		= -Wall -Wextra -Werror
LIBRARY     = libft/libft.a
################################################################################
# RULES																		   #
################################################################################

all: $(NAME)

$(NAME): $(LIBRARY) $(O_FILES)
	@$(CC) $(CFLAGS) $^ -o $@
	@echo && echo $(GREEN) "[√]     [$(NAME) Successfully Compiled!]"
	@echo $(WHITE)

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	@mkdir -p $(PATH_OBJ) $(O_DIR)
	@gcc -c -o $@ $(CFLAGS) $^ -I $(PATH_INC)/

$(LIBRARY):
	@make -C libft/

# - - - - - - - - — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

clean:
	@rm -rf $(shell find . -name '*.o')
	@rm -rf $(PATH_OBJ)
	@make clean -C libft/

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all

re: fclean $(NAME)

# Text Colorization — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
GREEN = "\033[1;32m"
WHITE = "\033[1;37m"

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —

.PHONY: all clean fclean re

# — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —