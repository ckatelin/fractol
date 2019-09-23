MLX_FLAGS	= -lmlx -framework OpenGL -framework AppKit


all: $(NAME)

$(NAME):
	gcc $(MLX_FLAGS) main.c -I fractol.h

clean:
	rm -rf a.out

fclean: clean