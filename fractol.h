#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./minilibx_macos/mlx.h"
#define HEIGHT 1080
#define WIDTH 1920

typedef struct s_complex
{	
	double re;
	double im;
}               t_complex;

typedef	struct s_fractol
{
	void	*connect;
	void	*window;
	void	*image;
	int		*pix_buf;
}				t_fractol;

int	close_window(int key, t_fractol *fractol);
t_complex init_complex(double re, double im);
t_fractol *all_fractols(t_fractol *fractol, int max_iteration, t_complex min, t_complex max, t_complex factor);