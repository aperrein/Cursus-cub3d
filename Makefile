# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcreus <mcreus@student.42perpignan.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 15:02:00 by aperrein          #+#    #+#              #
#    Updated: 2023/10/05 10:03:23 by mcreus           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

LIBFT = 	libft/libft.a

L = 		libft/

OBJ_DIR =	OBJ/

SRC_DIR =	SRC/

SRC	=	main.c conf_init.c conf_check.c error_conf.c  \
		check_color.c raycasting_init.c moves.c utils.c \
		raycasting.c raycasting2.c check_map_test.c mlx_destroy.c \
		raycasting3.c

OBJ	=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

RM	=	rm -f

CFLAGS	=	-Werror -Wall -Wextra

all     :       $(OBJ_DIR) $(NAME)
	
$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		gcc $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR) :
		mkdir $(OBJ_DIR)

$(NAME)	:	$(OBJ) $(L)
		@echo "\033[0;33m\COMPILING libft\n"
		make -s -C libft/
		@echo "\033[1;32mLIBFT created\n"
		@echo "\033[0;33m\nCOMPILING mlx\n"
		make -s -C minilibx
		@echo "\033[1;32mMLX created\n"
		@echo "\033[0;33m\nCOMPILING CUB3D.....\n"
		gcc $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) minilibx/libmlx.a -lX11 -lXext -lm
		@echo "\033[1;32m./cub3d created\n"

clean	:
		@echo "\033[0;31mDELETING MLX files\nLIBFT files\nCUB3D object...\n"
		$(RM) $(OBJ)
		make clean -C libft/
		make clean -C minilibx/
		@echo "033[1;32mDONE\n"

fclean	:	clean
		@echo "\033[0;31mDELETING CUB3D EXECUTABLE...."
		$(RM) $(NAME)
		make fclean -C libft/
		@echo "\033[1;32mDONE\n"

re 	:	fclean all
