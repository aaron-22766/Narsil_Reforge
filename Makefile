# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/01/26 14:34:00 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Narsil_Reforge

SRCDIR		=	./src
OBJDIR		=	./obj
LIBDIR		=	./lib

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-f

LIBFT_DIR	= $(LIBDIR)/libft
LIBFT_LIB	= libft.a
LIBFT		= $(LIBFT_DIR)/$(LIBFT_LIB)

MLX_DIR		= $(LIBDIR)/mlx
MLX_LIB		= libmlx42.a
MLX			= $(MLX_DIR)/$(MLX_LIB)

ARCS		=	$(LIBFT) $(MLX)
GLFW		=	-lglfw -L "$(HOME)/.brew/Cellar/glfw/3.3.8/lib"

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(ARCS) $(GLFW)

$(LIBFT): $(LIBDIR)
	git clone https://github.com/aaron-22766/libft.git $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(MLX): $(LIBDIR)
	git clone https://github.com/codam-coding-college/MLX42 $(MLX_DIR); make -C $(MLX_DIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(wildcard $(OBJDIR)/*.o)
	if [ -d $(OBJDIR) ]; then $(RM) -R $(RMFLAGS) $(OBJDIR); fi
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) fclean

libclean: fclean
	$(RM) -R $(RMFLAGS) $(LIBDIR)

re: fclean all

testall: maps/*/* | $(NAME)
	@for file in $^ ; do \
		echo "\nRUNNING: " $${file} ; \
		./$(NAME) $${file} ; \
	done
	@echo "\n\n\n\n\nEND OF TEST"

.PHONY: all clean fclean re testall