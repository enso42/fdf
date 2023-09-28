/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 13:41:59 by jmuller           #+#    #+#             */
/*   Updated: 2023/08/28 17:54:33 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

void	make_isometric(t_node *node, double angle)
{
	node->x = (node->x - node->y) * cos(angle);
	node->y = (node->x + node->y) * sin(angle) - node->z;
}

void	set_zoom(t_node *p1, t_node *p2, t_fdf *fdf)
{
	p1->x *= fdf->scale;
	p1->y *= fdf->scale;
	p2->x *= fdf->scale;
	p2->y *= fdf->scale;
}

void	set_color(t_node *p1, t_node *p2, t_fdf *fdf)
{
	if (p1->z != 0 || p2->z != 0)
	{
		if (p1->is_color)
			fdf->color = p1->is_color;
		else if (p2->is_color)
			fdf->color = p2->is_color;
		else
			fdf->color = 0xFF00FFFF;
	}
	else
		fdf->color = 0x0000FFFF;
}

void	is_colorcheck(int i, int j, t_node **points, char **arr)
{
	char		*color_str;
	long long	color;
	int			k;

	k = 0;
	if (ft_strchr(arr[j], ','))
	{
		while (arr[j][k] != 'x')
			k++;
		color_str = ft_substr(arr[j], k + 1, 6);
		color = hex_to_dec(color_str);
		free (color_str);
		points[i][j].is_color = color;
	}
	else
		points[i][j].is_color = 0xFFFFFFFF;
}
