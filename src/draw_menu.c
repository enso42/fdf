/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 11:20:16 by jmuller           #+#    #+#             */
/*   Updated: 2023/07/13 12:16:56 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

void	draw_menu(t_fdf *fdf)
{
	mlx_put_string(fdf->mlx_key, "MENU BAR", 20, 20);
	mlx_put_string(fdf->mlx_key, "--------", 20, 40);
	mlx_put_string(fdf->mlx_key, "Shift Drawing: Use Cursors", 20, 55);
	mlx_put_string(fdf->mlx_key, "Rotate: A, S", 20, 75);
	mlx_put_string(fdf->mlx_key, "Change Z-Axis: Z, X", 20, 95);
	mlx_put_string(fdf->mlx_key, "Zoom IN/OUT: C, V", 20, 115);
	mlx_put_string(fdf->mlx_key, "Isometric ON/OFF: B, N", 20, 135);
}
