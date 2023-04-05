# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/04/05 21:32:33 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Narsil_Reforge

SRCDIR		=	./src
OBJDIR		=	./obj
LIBDIR		=	./lib

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

DISPLAY_FPS	=	-D DISPLAY_FPS=$(shell if [[ $$(system_profiler SPDisplaysDataType | grep "Display Type: Built-in Liquid Retina XDR Display") ]]; then echo 120; else echo 60; fi)

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra $(DISPLAY_FPS)

RM			=	rm
RMFLAGS		=	-Rf

LIBFT_DIR	=	$(LIBDIR)/libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

MLX_DIR		=	$(LIBDIR)/mlx
MLX_LIB		=	libmlx42.a
MLX			=	$(MLX_DIR)/$(MLX_LIB)

ARCS		=	$(LIBFT) $(MLX)
GLFW		=	-lglfw -L "$(HOME)/.brew/opt/glfw/lib/"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(ARCS) $(GLFW)

$(LIBFT): $(LIBDIR)
	git clone https://github.com/aaron-22766/libft.git $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(MLX): $(LIBDIR)
	git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR); (cd $(MLX_DIR) && cmake -B . && make -j4)

$(LIBDIR):
	mkdir -p $(LIBDIR)
ifeq ($(shell which brew),$(HOME)/.brew/bin/brew)
	brew install glfw
	brew install cmake
else
	@echo "Please install brew!"
endif

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(OBJDIR)
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean/fast

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

libclean:
	$(RM) $(RMFLAGS) $(LIBDIR)

flibclean: fclean libclean

re: fclean all

testall: maps/*/* maps/* | $(NAME)
	@for file in $^ ; do \
		echo "\nRUNNING: " $${file} ; \
		./$(NAME) $${file} ; \
	done
	@echo "\n\n\n\n\nEND OF TEST"

.PHONY: all clean fclean libclean re testall
