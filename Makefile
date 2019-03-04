# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sechang <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/17 13:39:01 by sechang           #+#    #+#              #
#    Updated: 2019/03/03 21:50:43 by sechang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS = main.c init.c output.c usage.c ls_sorting.c open_dir_files.c
OBJ = ${SRCS:.c=.o}
FLAGS = -Wall -Werror -Wextra
LIB = Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	@make -C Libft
	@gcc $(FLAGS) $(OBJ) $(LIB) -o $@
	@echo "\033[1;32m[Compiled]\033[0m: \033[1;33m./ft_ls\033[0m"

%.o: %.c
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm $(OBJ)
	clear
	@echo "\033[1;31m[Removed]\033[0mft_ls select object files"

fclean: clean
	@rm $(NAME)

re: fclean all
