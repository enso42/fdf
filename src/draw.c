/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jmuller <jmuller@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/06/14 18:08:09 by jmuller		   #+#	#+#			 */
/*   Updated: 2023/07/05 16:10:59 by jmuller		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

void	set_z_scale(t_node *p1, t_node *p2, t_fdf *fdf)
{
	p1->z *= fdf->z_scale;
	p2->z *= fdf->z_scale;
}

void	node_tuning(t_node *p1, t_node *p2, t_fdf *fdf)
{
	set_zoom(p1, p2, fdf);
	set_color(p1, p2, fdf);
	set_z_scale(p1, p2, fdf);
	if (fdf->is_isometric == 1)
	{
		make_isometric(p1, fdf->angle);
		make_isometric(p2, fdf->angle);
	}
	shift_to_center(p1, p2, fdf);
}

void	draw_helper(mlx_image_t *img, t_node p1, t_node p2, t_fdf *fdf)
{
	while (p1.x != p2.x || p1.y != p2.y)
	{
		if ((p1.x >= 0 && p1.x <= fdf->win_x - 1)
			&& (p1.y >= 0 && p1.y <= fdf->win_y - 1))
		{
			mlx_put_pixel(img, p1.x, p1.y, fdf->color);
		}
		fdf->val.err2 = fdf->val.err1;
		if (fdf->val.err2 > -fdf->val.dx)
		{
			fdf->val.err1 -= fdf->val.dy;
			p1.x += fdf->val.step_x;
		}
		if (fdf->val.err2 < fdf->val.dy)
		{
			fdf->val.err1 += fdf->val.dx;
			p1.y += fdf->val.step_y;
		}
		if (p1.x >= fdf->win_x - 1 || p1.y >= fdf->win_y - 1 || p1.x < 0
			|| p1.y < 0)
			break ;
	}
}

void	draw_line(mlx_image_t *img, t_node p1, t_node p2, t_fdf *fdf)
{
	node_tuning(&p1, &p2, fdf);
	fdf->val.dx = abs(p2.x - p1.x);
	fdf->val.dy = abs(p2.y - p1.y);
	if (p1.x < p2.x)
		fdf->val.step_x = 1;
	else
		fdf->val.step_x = -1;
	if (p1.y < p2.y)
		fdf->val.step_y = 1;
	else
		fdf->val.step_y = -1;
	if (fdf->val.dx > fdf->val.dy)
		fdf->val.err1 = fdf->val.dx / 2;
	else
		fdf->val.err1 = -fdf->val.dy / 2;
	draw_helper(img, p1, p2, fdf);
}

void	draw(void *ptr)
{
	int		i;
	int		j;
	t_node	**point;
	t_fdf	*fdf;

	fdf = (t_fdf *)ptr;
	point = fdf->matrix;
	i = 0;
	while (i < fdf->height)
	{
		j = 0;
		while (1)
		{
			if ((point[i + 1] && point[i + 1] != NULL))
				draw_line(fdf->img_key, point[i][j], point[i + 1][j], fdf);
			if (!point[i][j].is_last)
				draw_line(fdf->img_key, point[i][j], point[i][j + 1], fdf);
			if (point[i][j].is_last)
				break ;
			j++;
		}
		i++;
	}
}
