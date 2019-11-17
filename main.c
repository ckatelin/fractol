
#include "fractol.h"

void			keys(t_fractol *fractol)
{
//	mlx_hook(fractol->window, 2, 0, key_press, fractol);
//	mlx_hook(fractol->window, 4, 0, mouse_press, fractol);
//	mlx_hook(fractol->window, 5, 0, mouse_release, fractol);
//	mlx_hook(fractol->window, 6, 0, mouse_move, fractol);
//	mlx_hook(fractol->window, 12, 0, expose, fractol);
//	mlx_hook(fractol->window, 2, 0, key_hook, fractol);
//	mlx_hook(fractol->window, 6, 0, (int (*)())mouse_move, fractol);
//	mlx_hook(fractol->window, 4, 0, mouse_event, fractol);
//	mlx_hook(fractol->window, 17, 0, (int (*)())exit, fractol);
	mlx_hook(fractol->window, 2, 0, close_window, fractol);
}

t_complex init_complex(double re, double im)
{
    t_complex complex;

    complex.re = re;
    complex.im = im;
    return (complex);
}

t_fractol	*init_fractol(t_fractol *fractol)
{
	int bits_per_pix;
	int line_size;
	int endian;

//	if (!fractol)
//		fractol = (t_fractol *)malloc(sizeof(fractol));
	fractol->connect = mlx_init();
	fractol->window = mlx_new_window(fractol->connect, 1920, 1080, "fractol");
	fractol->image = mlx_new_image(fractol->connect, 1920, 1080);
	fractol->pix_buf = (int *)mlx_get_data_addr(fractol->image, &bits_per_pix, &line_size, &endian);
	return(fractol);
}

int main(void)
{
	int i = 0;
	int j = 0;
	int x;
	int y;
	int iteration;
	t_complex z;
	double t;
	int red;
	int green;
	int blue;
	int max_iteration;
	t_complex min;
	t_complex max;
	t_complex factor;
	t_complex c;
	int colour;
	t_fractol *fractol;


	if (!fractol)
		fractol = (t_fractol *)malloc(sizeof(fractol));
	fractol = init_fractol(fractol);

	max_iteration = 50;
	min = init_complex(-2.0, -2.0);
	max.re = 5.0;
	max.im = min.im + (max.re - min.re) * HEIGHT / WIDTH;

	factor = init_complex(
	(max.re - min.re) / (WIDTH - 1),
	(max.im - min.im) / (HEIGHT - 1));
	fractol = all_fractols(fractol, max_iteration, min, max, factor);
	mlx_put_image_to_window(fractol->connect, fractol->window, fractol->image, 0, 0);
	keys(fractol);
	mlx_loop(fractol->connect);
	return (0);
}