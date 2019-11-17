
#include "fractol.h"

void			keys(t_fractol *fractol)
{
//	mlx_hook(fractol->window, 2, 0, key_press, fractol);
//	mlx_hook(fractol->window, 4, 0, mouse_press, fractol);
//	mlx_hook(fractol->window, 5, 0, mouse_release, fractol);
//	mlx_hook(fractol->window, 6, 0, mouse_move, fractol);
//	mlx_hook(fractol->window, 12, 0, expose, fractol);
	mlx_hook(fractol->mlx.window, 2, 0, key_hook, fractol);
//	mlx_hook(fractol->window, 6, 0, (int (*)())mouse_move, fractol);
//	mlx_hook(fractol->window, 4, 0, mouse_event, fractol);
//	mlx_hook(fractol->window, 17, 0, (int (*)())exit, fractol);
	mlx_hook(fractol->mlx.window, 2, 0, close_window, fractol);
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
	fractol->min = init_complex(-4.0, -2.0); //цифры могут быть другими
	fractol->max.re = 5.0; //цифры могут быть другими
	fractol->max.im = fractol->min.im + (fractol->max.re - fractol->min.re) * HEIGHT / WIDTH;
	fractol->zoom = 25;
//	fractol->k = init_complex(-0.9, 0.3);
	fractol->max_iter = 50;
	fractol->r = 16;
	fractol->g = 8;
	fractol->b = 0;
	fractol->factor = init_complex(
		(fractol->max.re - fractol->min.re) / (WIDTH - 1),
		(fractol->max.im - fractol->min.im) / (HEIGHT - 1));
	return(fractol);
}

t_fractol	*init_mlx(t_fractol *fractol)
{
	int bits_per_pix;
	int line_size;
	int endian;

	if(!fractol)
		fractol = (t_fractol *)malloc(sizeof(fractol));
	fractol->mlx.connect = mlx_init();
	fractol->mlx.window = mlx_new_window(fractol->mlx.connect, 1920, 1080, "fractol");
	fractol->mlx.image = mlx_new_image(fractol->mlx.connect, 1920, 1080);
	fractol->mlx.pix_buf = (int *)mlx_get_data_addr(fractol->mlx.image, &bits_per_pix, &line_size, &endian);
	return(fractol);
}

int main(void)
{
	t_fractol *fractol;
	int bits_per_pix;
	int line_size;
	int endian;
	int k = 0;

	fractol = init_mlx(fractol);
	fractol = init_fractol(fractol);
//	fractol = all_fractols(fractol);
//	keys(fractol);
	mlx_hook(fractol->mlx.window, 2, 0, key_hook, fractol);
	mlx_hook(fractol->mlx.window, 2, 0, close_window, fractol);
	fractol = all_fractols(fractol);
	mlx_put_image_to_window(fractol->mlx.connect, fractol->mlx.window, fractol->mlx.image, 0, 0);
	mlx_loop(fractol->mlx.connect);
	return (0);
}