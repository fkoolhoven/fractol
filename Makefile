NAME		= fractol
CFLAGS		= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX		= ./lib/MLX42
LIBFT		= $(addprefix $(LIBFT_DIR)/,libft.a)
LIBFT_DIR	= includes/libft
HEADERS		= -I ./includes -I $(LIBMLX)/include
LIBS		= $(LIBMLX)/build/libmlx42.a -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
SRCS		= fractol.c parameters.c hooks.c coloring.c palette.c mandelbrot.c julia.c
OBJS		= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && echo "Compiling: $(notdir $<)" 

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(LIBFT) $(HEADERS) -o $(NAME)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	@rm -f $(OBJS)
	@rm -f $(LIBMLX)/build

fclean: clean
	make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx