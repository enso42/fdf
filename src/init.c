/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:01:06 by jmuller           #+#    #+#             */
/*   Updated: 2023/07/13 12:16:15 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

int	line_condition(int flag, int true_con, int false_con)
{
	if (flag)
	{
		return (true_con);
	}
	return (false_con);
}

int	find_scale(t_fdf *fdf)
{
	int	x_scale;
	int	y_scale;

	x_scale = fdf->win_x / fdf->height;
	y_scale = fdf->win_y / fdf->width;
	return (line_condition(x_scale > y_scale, y_scale, x_scale));
}

void	default_graphics_setting(t_fdf *fdf)
{
	fdf->win_x = 1920;
	fdf->win_y = 1080;
	fdf->scale = find_scale(fdf);
	fdf->z_scale = 1;
	fdf->is_isometric = 1;
	fdf->angle = 0.523599;
	fdf->shift_x = fdf->win_x / 2;
	fdf->shift_y = fdf->win_y / 3;
	fdf->color = 0;
}
