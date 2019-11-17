#include "fractol.h"

t_fractol *all_fractols(t_fractol *fractol)
{
	int y;
	t_complex c;
	int x;
	int iteration;
	t_complex z;
	double t;
//	int red;
//	int green;
//	int blue;
//	int colour;

	y = 0;
	while (y < HEIGHT)
	{
	    c.im = fractol->max.im - y * fractol->factor.im;
	    x = 0;
	    while (x < WIDTH)
		{
	        c.re = fractol->min.re + x * fractol->factor.re;
		    z = init_complex(c.re, c.im);
    	    iteration = 0;
			while (pow(z.re, 2.0) + pow(z.im, 2.0) <= 4
            	&& iteration < fractol->max_iter)
        	{
            	z = init_complex(
            	pow(z.re, 2.0) - pow(z.im, 2.0) + c.re,
            	2.0 * z.re * z.im + c.im);
            	iteration++;
        	}
//			colour = 0;
     		t = (double)iteration / (double)fractol->max_iter;
     		fractol->r = (int)(9 * (1 - t) * pow(t, 3) * 255);
     		fractol->g = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
    		fractol->b = (int)(8.5 * pow((1 - t), 3) * t * 255);
			fractol->mlx.pix_buf[y * WIDTH + x] = (fractol->r << 16) | (fractol->g << 8) | (fractol->b);
//			fractol->pix_buf[y * WIDTH + x] = colour;
    		x++;
    	}
		y++;
	}
	return(fractol);
}