NAME			= fractol
CC				= cc
CFLAGS			= -Wall -Wextra -Werror -Ofast
LIBS_DIR		= libraries
MLX_DIR			= $(LIBS_DIR)/MLX42
MLX_BUILD_DIR	= $(MLX_DIR)/build
MLX42			= $(MLX_BUILD_DIR)/libmlx42.a
LIBFT_DIR		= $(LIBS_DIR)/libft
LIBFT			= $(LIBFT_DIR)/libft.a
LIBS			= $(LIBFT) $(MLX42) -framework Cocoa -framework OpenGL -framework IOKit
INC         	= -I includes -I $(MLX_DIR)/include
SRCS			= main.c parameters.c hooks.c coloring.c palette.c fractals.c render.c
SRC_DIR 		= sources
OBJS			= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
OBJ_DIR 		= objects

all: libmlx $(NAME)

libmlx: $(MLX42)

#building graphics library MLX42
$(MLX42):
	@cmake $(MLX_DIR) -B $(MLX_BUILD_DIR) && make -C $(MLX_BUILD_DIR) -j4

#building executable 'fractol'
$(NAME): $(OBJS) $(MLX42) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(INC) -o $(NAME) -lglfw

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
	@rm -rf $(MLX_BUILD_DIR)
	@echo Removed MLX42 build directory

re: fclean all

.PHONY: all, libmlx, clean, fclean, re