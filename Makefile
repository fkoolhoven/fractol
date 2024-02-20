NAME		= fractol
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ofast
LIBMLX		= ./MLX42
LIBMLXBUILD	= ./MLX42/build
LIBFT_DIR	= includes/libft
LIBFT		= $(addprefix $(LIBFT_DIR)/,libft.a)
HEADERS		= -I ./includes -I $(LIBMLX)/include -lglfw
LIBS		= $(LIBMLXBUILD)/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit
SRCS		= main.c parameters.c hooks.c coloring.c palette.c fractals.c render.c
SRC_DIR 	= sources
OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
OBJ_DIR 	= objects

all: libmlx $(NAME)

libmlx: $(LIBMLX) $(LIBMLXBUILD)

#building graphics library MLX42
$(LIBMLXBUILD):
	@cmake $(LIBMLX) -B $(LIBMLXBUILD) && make -C $(LIBMLXBUILD) -j4

#building executable 'fractol'
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

#compiling source (.c) files into object (.o) files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

#building libft.a (customized C library)
$(LIBFT):
	@make bonus -C $(LIBFT_DIR)

#removing all object files and MLX42's build folder
clean:
	@make clean -C $(LIBFT_DIR)
	@echo Removed libft object files
	@rm -rf $(OBJ_DIR)
	@echo Removed objects directory and object files

#executing clean and removing libft.a and executable 'fractol'
fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@echo Removed libft.a
	@rm -f $(NAME)
	@echo Removed fractol
	@rm -rf $(LIBMLXBUILD)
	@echo Removed MLX42 build directory

re: clean all

.PHONY: all, libmlx, clean, fclean, libclean, re