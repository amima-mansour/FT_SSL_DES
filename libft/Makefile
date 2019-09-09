# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amansour <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/01 12:36:18 by amansour          #+#    #+#              #
#    Updated: 2019/08/19 17:48:30 by amansour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

PATH_SRC = src

SRC = $(addprefix $(PATH_SRC)/, \
	ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
	ft_lstmap.c ft_lstnew.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c \
	ft_putchar_fd.c ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c \
	ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c \
	ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c \
	ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
	ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c \
	ft_strnstr.c ft_strrchr.c ft_strsplit.c ft_strstr.c ft_strsub.c \
	ft_strtrim.c ft_tolower.c ft_toupper.c ft_isspace.c ft_sqrt.c ft_abs.c\
	ft_inverse.c ft_convert.c ft_realloc.c get_next_line.c\
	ft_printf.c conversion.c test.c util.c nbr_to_string.c\
	to_n.c to_p.c to_bigc.c to_bigs.c to_string.c display.c to_sign_decimal.c\
	to_decimal.c format.c\
	ft_wstrlen.c convert_unicode.c)

PATH_INC = inc
PATH_OBJ = obj
OBJ = $(SRC:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o)

all: $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo $(WHITE)
	@ranlib $(NAME)

$(PATH_OBJ)/%.o: $(addprefix $(PATH_SRC)/, %.c)
	@mkdir -p $(PATH_OBJ)
	@gcc -c -o $@ $(FLAGS) $^ -I $(PATH_INC)/

clean:
	@rm -rf  $(shell find . -name '*.o')
	@rm -rf $(PATH_OBJ)
	@rm -rf $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all


# Text Colorization — — — — — — — — — — — — — — — — — — — — — — — — — — — — — —
GREEN = "\033[1;32m"
WHITE = "\033[1;37m"

.PHONY: all clean fclean re
