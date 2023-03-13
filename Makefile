NAME		= fractol
CFLAGS		= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		= ./lib/MLX42
LIBFT		= $(addprefix $(LIBFT_DIR)/,libft.a)
LIBFT_DIR	= includes/libft
HEADERS		= -I ./includes -I $(LIBMLX)/include
LIBS		= $(LIBMLX)/build/libmlx42.a -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
SRCS		= main.c parameters.c hooks.c coloring.c palette.c fractals.c render.c
SRC_DIR 	= sources
OBJS		= $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
OBJ_DIR 	= objects

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM)r $(OBJ_DIR)
#	@rm -f $(LIBMLX)/build

fclean: clean
	make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx