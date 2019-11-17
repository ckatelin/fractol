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

typedef	struct s_mlx
{
	void	*connect;
	void	*window;
	void	*image;
	int		*pix_buf;
}				t_mlx;

typedef	struct s_fractol
{
	t_complex	min;
	t_complex	max;
	int	r;
	int g;
	int	b;
	double	zoom;
	int	max_iter;
	t_complex factor;
	t_mlx	mlx;
	double x;
	double y;

}				t_fractol;

int	close_window(int key, t_fractol *fractol);
t_complex init_complex(double re, double im);
t_fractol *all_fractols(t_fractol *fractol);
t_fractol	*init_mlx(t_fractol *fractol);
t_fractol	*init_fractol(t_fractol *fractol);
int key_hook(int key, t_fractol *fractol);
void	key_hook_color(t_fractol *fractol, int key);
void	key_hook_control(t_fractol *fractol, int key);
void		de_zoom(t_fractol *fractol);
void		zoom(t_fractol *fractol);
void	key_hook_move(t_fractol *fractol, int key, double offset);