# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/14 17:40:26 by arabenst          #+#    #+#              #
#    Updated: 2023/02/08 13:22:39 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Narsil_Reforge
120_NAME	=	Narsil_Reforge_120

SRCDIR		=	./src
OBJDIR		=	./obj
LIBDIR		=	./lib

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
120_OBJS	=	$(addprefix $(OBJDIR)/@120_,$(notdir $(SRCS:.c=.o)))

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-f

LIBFT_DIR	=	$(LIBDIR)/libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

MLX_DIR		=	$(LIBDIR)/mlx
MLX_LIB		=	libmlx42.a
MLX			=	$(MLX_DIR)/$(MLX_LIB)

ARCS		=	$(LIBFT) $(MLX)
GLFW		=	-lglfw -L "$(HOME)/.brew/opt/glfw/lib/"

all: 60

60: $(NAME)

120: $(120_NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(ARCS) $(GLFW)

$(120_NAME): $(LIBFT) $(MLX) $(120_OBJS)
	$(CC) -o $(120_NAME) $(CFLAGS) -D DISPLAY_FPS=120 $(120_OBJS) $(ARCS) $(GLFW)

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

$(OBJDIR)/@120_%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) -D DISPLAY_FPS=120 $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(RMFLAGS) $(wildcard $(OBJDIR)/*.o)
	if [ -d $(OBJDIR) ]; then $(RM) -R $(RMFLAGS) $(OBJDIR); fi
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean/fast

fclean: clean
	$(RM) $(RMFLAGS) $(NAME) $(120_NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) clean

libclean: fclean
	$(RM) -R $(RMFLAGS) $(LIBDIR)
	if [ -d $(LIBDIR) ]; then $(RM) -R $(RMFLAGS) $(LIBDIR); fi

re: fclean all

testall: maps/*/* maps/* | $(NAME)
	@for file in $^ ; do \
		echo "\nRUNNING: " $${file} ; \
		./$(NAME) $${file} ; \
	done
	@echo "\n\n\n\n\nEND OF TEST"

.PHONY: all clean fclean libclean re testall