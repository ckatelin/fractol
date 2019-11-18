/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckatelin <ckatelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 18:30:50 by ckatelin            #+#    #+#             */
/*   Updated: 2019/09/23 16:43:53 by ckatelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
/*
void	reset_mlx(t_mlx_var *mlx_var)
{
	mlx_var->linear_algebra.horizontal = 0;
	mlx_var->linear_algebra.vertical = 0;
	mlx_var->linear_algebra.angle_x = 1.100;
	mlx_var->linear_algebra.angle_y = 0;
	mlx_var->linear_algebra.angle_z = -0.880;
	mlx_var->mouse.move_sensitivity = 1.0;
	mlx_var->mouse.rot_sensitivity = 0.0030;
	mlx_var->flags.z_axis_mode = 1;
	mlx_var->flags.debug_mode = 0;
	mlx_var->screen.altitude = 1.0;
	mlx_var->flags.hint = 0;
}

int		change_color(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 83 && (mlx_var->color.start = 0x6749D7))
		mlx_var->color.final = 0xE439A1;
	else if (key_code == 84 && (mlx_var->color.start = 0x007D1C))
		mlx_var->color.final = 0x8C6DD7;
	else if (key_code == 85 && (mlx_var->color.start = 0xDC0055))
		mlx_var->color.final = 0x34D0B6;
	else if (key_code == 86 && (mlx_var->color.start = 0xDB0058))
		mlx_var->color.final = 0x172CAF;
	else if (key_code == 87 && (mlx_var->color.start = 0x37DC74))
		mlx_var->color.final = 0xD6FA3F;
	else
		return (0);
	initialize_color(mlx_var);
	return (1);
}

int		key_press2(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 4)
		if (!mlx_var->flags.hint)
			mlx_var->flags.hint = 1;
		else
			mlx_var->flags.hint = 0;
	else if (key_code == 2)
		if (!mlx_var->flags.debug_mode)
			mlx_var->flags.debug_mode = 1;
		else
			mlx_var->flags.debug_mode = 0;
	else if (key_code == 49)
		reset_mlx(mlx_var);
	else if (key_code == 53)
	{
		mlx_destroy_window(mlx_var->io, mlx_var->window);
		to_free_list(&mlx_var->maps, mlx_var->maps->prev->count);
		error_handler(EMERGENCY_EXIT);
	}
	else if (change_color(key_code, mlx_var))
		;
	else
		return (0);
	return (1);
}

int		key_press(int key_code, t_mlx_var *mlx_var)
{
	if (key_code == 69)
		mlx_var->screen.altitude *= 1.05;
	else if (key_code == 78)
		mlx_var->screen.altitude *= 0.95;
	else if (key_code == 116)
		mlx_var->mouse.rot_sensitivity += 0.0001;
	else if (key_code == 115)
		mlx_var->mouse.move_sensitivity += 0.1;
	else if (key_code == 121)
		mlx_var->mouse.rot_sensitivity > 0.0001 ?
		mlx_var->mouse.rot_sensitivity -= 0.0001 :
		(mlx_var->flags.hint = 1);
	else if (key_code == 119)
		mlx_var->mouse.move_sensitivity > 0.1 ?
		mlx_var->mouse.move_sensitivity -= 0.1 :
		(mlx_var->flags.hint = 1);
	else if (key_code == 6)
		mlx_var->flags.z_axis_mode == 0 ?
		mlx_var->flags.z_axis_mode = 1 :
		(mlx_var->flags.z_axis_mode = 0);
	else if (key_press2(key_code, mlx_var))
		;
	x_y_z_axis_rotation(mlx_var);
	display_pixels(mlx_var);
	return (0);
}
*/
int		close_window(int key, t_fractol	*fractol)
{
	if (key == 53)
	{
		mlx_destroy_window(fractol->mlx.connect, fractol->mlx.window);
		exit (0);
	}
	return (0);
}

void	key_hook_move(t_fractol *fractol, int key, double offset)
{
	if (key == 124)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.re = fractol->min.re - offset;
		fractol->max.re = fractol->max.re - offset;
	}
	if (key == 125)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.im = fractol->min.im + offset;
		fractol->max.im = fractol->max.im + offset;
	}
	if (key == 126)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.im = fractol->min.im - offset;
		fractol->max.im = fractol->max.im - offset;
	}
	if (key == 123)
	{
		offset = ((fractol->max.re - fractol->min.re) / fractol->zoom) / 2;
		fractol->min.re = fractol->min.re + offset;
		fractol->max.re = fractol->max.re + offset;
	}
}

void		de_zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_complex	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	cent.re = (fractol->x / x_m) + fractol->min.re;
	cent.im = -((fractol->y / y_m) - fractol->max.im);
	fractol->min.re = fractol->min.re -
	(cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re +
	(fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im -
	(cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im +
	(fractol->max.im - cent.im) / fractol->zoom;
}

void		zoom(t_fractol *fractol)
{
	double	x_m;
	double	y_m;
	t_complex	cent;

	x_m = WIDTH / (fractol->max.re - fractol->min.re);
	y_m = HEIGHT / (fractol->max.im - fractol->min.im);
	cent.re = (fractol->x / x_m) + fractol->min.re;
	cent.im = -((fractol->y / y_m) - fractol->max.im);
	fractol->min.re = fractol->min.re +
	(cent.re - fractol->min.re) / fractol->zoom;
	fractol->max.re = fractol->max.re -
	(fractol->max.re - cent.re) / fractol->zoom;
	fractol->min.im = fractol->min.im +
	(cent.im - fractol->min.im) / fractol->zoom;
	fractol->max.im = fractol->max.im -
	(fractol->max.im - cent.im) / fractol->zoom;
}

void	key_hook_control(t_fractol *fractol, int key)
{
/*	if (key == 116)
	{
		if (fractol->id == 5)
			fractol->id = 1;
		else
			fractol->id++;
		init_fractol(fractol);
	}*/
	if (key == 67)
		fractol->max_iter++;
	if (key == 75)
		fractol->max_iter--;
	if (key == 27)
		de_zoom(fractol);
	if (key == 24)
		zoom(fractol);
	printf("%d\n", fractol->max_iter);
	if (key == 53)
	{
		mlx_destroy_window(fractol->mlx.connect, fractol->mlx.window);
		exit (0);
	}
//	if (key == 53)
//		exit(0);
/*	if (key == 49 && (fractol->id == 2 || fractol->id == 5))
	{
		if (fractol->space == 0)
			fractol->space = 1;
		else
			fractol->space = 0;
	}*/
}

void	key_hook_color(t_fractol *fractol, int key)
{
	if (key == 83)
		if (fractol->r != 16)
			fractol->r++;
	if (key == 84)
		if (fractol->g != 16)
			fractol->g++;
	if (key == 85)
		if (fractol->b != 16)
			fractol->b++;
	if (key == 86)
		if (fractol->r != 0)
			fractol->r--;
	if (key == 87)
		if (fractol->g != 0)
			fractol->g--;
	if (key == 88)
		if (fractol->b != 0)
			fractol->b--;
//	if (key == 15)
//		init_fractol(fractol);
}

int key_hook(int key, t_fractol *fractol)
{
	double	offset;

	offset = 0.0;
	key_hook_color(fractol, key);
	key_hook_control(fractol, key);
	key_hook_move(fractol, key, offset);
	return (0);
}