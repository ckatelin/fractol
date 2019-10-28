MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit
NAME = fractol

all: $(NAME)

$(NAME):
	gcc $(MLX_FLAGS) main.c all_keys.c all_fractols.c -I fractol.h

clean:
	rm -rf a.out

fclean: clean