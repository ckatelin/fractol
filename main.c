
#include "fractol.h"

void			keys(t_fractol *fractol)
{
//	mlx_hook(fractol->window, 2, 0, key_press, fractol);
//	mlx_hook(fractol->window, 4, 0, mouse_press, fractol);
//	mlx_hook(fractol->window, 5, 0, mouse_release, fractol);
//	mlx_hook(fractol->window, 6, 0, mouse_move, fractol);
//	mlx_hook(fractol->window, 12, 0, expose, fractol);
	mlx_hook(fractol->window, 2, 0, close_window, fractol);
}

t_complex init_complex(double re, double im)
{
    t_complex complex;

    complex.re = re;
    complex.im = im;
    return (complex);
}

void    mak(void)
{
    int x;
    int y;
    int iteration;
	t_complex z;
    int t;
    int red;
    int green;
    int blue;
    int max_iteration;
	t_complex min;
	t_complex max;
	t_complex factor;
	t_complex c;


    max_iteration = 50;
    min = init_complex(-2.0, -2.0);
    max.re = 2.0;
    max.im = min.im + (max.re - min.re) * HEIGHT / WIDTH;

	factor = init_complex(
    (max.re - min.re) / (WIDTH - 1),
    (max.im - min.im) / (HEIGHT - 1));
    y = HEIGHT;
    while (y < HEIGHT)
    {
        c.im = max.im - y * factor.im;
        x = 0;
        while (x < WIDTH)
        {
            c.re = min.re + x * factor.re;
            z = init_complex(c.re, c.im);
            iteration = 0;
            while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
                && iteration < max_iteration)
            {
                z = init_complex(
                pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
                2.0 * z.re * z.im + c.im);
                iteration++;
            }
        	t = (double)iteration / (double)max_iteration;
        	red = (int)(9 * (1 - t) * pow(t, 3) * 255);
        	green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
        	blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
        	x++;
        }
    	y++;
    }
}

int main(void)
{

	int bits_per_pix;
	int line_size;
	int endian;
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



	fractol->connect = mlx_init();
	fractol->window = mlx_new_window(fractol->connect, 1920, 1080, "fractol");
	fractol->image = mlx_new_image(fractol->connect, 1920, 1080);
	fractol->pix_buf = (int *)mlx_get_data_addr(fractol->image, &bits_per_pix, &line_size, &endian);


	max_iteration = 50;
	min = init_complex(-2.0, -2.0);
	max.re = 5.0;
	max.im = min.im + (max.re - min.re) * HEIGHT / WIDTH;

	factor = init_complex(
	(max.re - min.re) / (WIDTH - 1),
	(max.im - min.im) / (HEIGHT - 1));
	y = 0;
	while (y < HEIGHT)
	{
	    c.im = max.im - y * factor.im;
	    x = 0;
	    while (x < WIDTH)
		{
	        c.re = min.re + x * factor.re;
		    z = init_complex(c.re, c.im);
    	    iteration = 0;
			while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
            	&& iteration < max_iteration)
        	{
            	z = init_complex(
            	pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
            	2.0 * z.re * z.im + c.im);
            	iteration++;
        	}
			colour = 0;
     		t = (double)iteration / (double)max_iteration;
     		red = (int)(9 * (1 - t) * pow(t, 3) * 255);
     		green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
    		blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
			colour = (red << 16) | (green << 8) | (blue);
//			if ((y * WIDTH + x + HEIGHT / 2) < WIDTH * HEIGHT)
			fractol->pix_buf[y * WIDTH + x] = colour;
    		x++;
    	}
		y++;
	}
	mlx_put_image_to_window(fractol->connect, fractol->window, fractol->image, 0, 0);
	keys(fractol);
	mlx_loop(fractol->connect);
	return (0);
}