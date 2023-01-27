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

NAME		=	so_long
BON_NAME	=	so_long_bonus

SRCDIR		=	./src
BONDIR		=	./bonus
OBJDIR		=	./obj
BONOBJDIR	=	./bonus_obj
LIBDIR		=	./lib

SRCS		=	$(wildcard $(SRCDIR)/*.c)
OBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SRCS:.c=.o)))
BONSRCS		=	$(wildcard $(BONDIR)/*.c)
BONOBJS		=	$(addprefix $(BONOBJDIR)/,$(notdir $(BONSRCS:.c=.o)))

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

BREW		= rm -rf $(HOME)/.brew && git clone --depth=1 https://github.com/Homebrew/brew $(HOME)/.brew && echo 'export PATH=$(HOME)/.brew/bin:$(PATH)' >> $(HOME)/.zshrc && source $(HOME)/.zshrc && brew update

ARCS		=	$(LIBFT) $(MLX)
GLFW		=	-lglfw -L "$(HOME)/.brew/opt/glfw/lib/"

$(NAME): check_brew

compile: $(LIBFT) $(MLX) $(OBJS)
	$(CC) -o $(NAME) $(CFLAGS) $(OBJS) $(ARCS) $(GLFW)

compile_bonus: $(LIBFT) $(MLX) $(BONOBJS)
	$(CC) -o $(BON_NAME) $(CFLAGS) $(BONOBJS) $(ARCS) $(GLFW)

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

$(BONOBJDIR)/%.o: $(BONDIR)/%.c | $(BONOBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BONOBJDIR):
	mkdir -p $(BONOBJDIR)

all: $(NAME)

clean:
	$(RM) $(RMFLAGS) $(wildcard $(OBJDIR)/*.o)
	$(RM) $(RMFLAGS) $(wildcard $(BONOBJDIR)/*.o)
	if [ -d $(OBJDIR) ]; then rm -Rf $(OBJDIR); fi
	if [ -d $(BONOBJDIR) ]; then rm -Rf $(BONOBJDIR); fi
	make -C $(LIBFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(NAME) $(BON_NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(MLX_DIR) fclean

re: fclean all

mandatory: check_brew

bonus: check_brew_bonus

testall: maps/*/* | $(NAME)
	@for file in $^ ; do \
		echo "\nRUNNING: " $${file} ; \
		./$(NAME) $${file} ; \
	done
	@echo "\n\n\n\n\nEND OF TEST"

check_brew: compile
# ifeq ($(shell which brew),$(HOME)/.brew/bin/brew)
# 	@echo "Brew is installed"
# 	make glfw
# 	make compile
# else
# 	@echo "No current Brew found"
# 	@echo "Pls install Brew by using make brew or skip by using make compile"
# endif

check_brew_bonus: compile_bonus
# ifeq ($(shell which brew),$(HOME)/.brew/bin/brew)
# 	@echo "Brew is installed"
# 	make glfw
# 	make compile_bonus
# else
# 	@echo "No current Brew found"
# 	@echo "Pls install Brew by using make brew or skip by using make compile"
# endif

glfw:
	brew install glfw

brew:
	$(shell $(BREW))

.PHONY: all clean fclean re testall compile compile_bonus mandatory bonus check_brew check_brew_bonus glfw brew