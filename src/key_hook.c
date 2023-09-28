/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:59:25 by jmuller           #+#    #+#             */
/*   Updated: 2023/07/13 12:16:04 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

void	move(mlx_key_data_t keydata, t_fdf *fdf)
{
	if (keydata.key == 262)
		fdf->shift_x += 5;
	if (keydata.key == 263)
		fdf->shift_x -= 5;
	if (keydata.key == 264)
		fdf->shift_y += 5;
	if (keydata.key == 265)
		fdf->shift_y -= 5;
}

void	navigation(mlx_key_data_t keydata, t_fdf *fdf)
{
	move(keydata, fdf);
	if (keydata.key == MLX_KEY_Z)
		fdf->z_scale += 1;
	if (keydata.key == MLX_KEY_X)
		fdf->z_scale -= 1;
	if (keydata.key == MLX_KEY_C)
		fdf->scale += 2;
	if (keydata.key == MLX_KEY_V)
		fdf->scale -= 2;
	if (keydata.key == MLX_KEY_B)
		fdf->is_isometric = 1;
	if (keydata.key == MLX_KEY_N)
		fdf->is_isometric = 0;
	if (keydata.key == MLX_KEY_A)
		fdf->angle += 0.05;
	if (keydata.key == MLX_KEY_S)
		fdf->angle -= 0.5;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(fdf->mlx_key);
}

void	key_hook(mlx_key_data_t keydata, void *para)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)para;
	navigation(keydata, fdf);
	mlx_delete_image(fdf->mlx_key, fdf->img_key);
	fdf->img_key = mlx_new_image(fdf->mlx_key,
			fdf->win_x, fdf->win_y);
	mlx_image_to_window(fdf->mlx_key, fdf->img_key, 0, 0);
}
