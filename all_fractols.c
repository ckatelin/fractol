#include "fractol.h"

t_fractol *all_fractols(t_fractol *fractol, int max_iteration, t_complex min, t_complex max, t_complex factor)
{
	int y;
	t_complex c;
	int x;
	int iteration;
	t_complex z;
	double t;
	int red;
	int green;
	int blue;
	int colour;

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
			fractol->pix_buf[y * WIDTH + x] = colour;
    		x++;
    	}
		y++;
	}
	return(fractol);
}