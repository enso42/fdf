/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_matrix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:59:14 by jmuller           #+#    #+#             */
/*   Updated: 2023/08/29 10:05:56 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

void	is_lastcheck(t_node **points, int i, int j, int col)
{
	printf("i: %d, j: %d, col: %d\n", i, j, col);
	if (j == (col -1))
		points[i][j].is_last = 1;
	else
		points[i][j].is_last = 0;
}

void	shift_to_center(t_node *p1, t_node *p2, t_fdf *fdf)
{
	p1->x += fdf->shift_x;
	p1->y += fdf->shift_y;
	p2->x += fdf->shift_x;
	p2->y += fdf->shift_y;
}

void	build_matrix(int i, int col, t_node **points, char *line)
{
	int		j;
	char	**arr;

	j = 0;
	arr = ft_split(line, ' ');
	while (j < col)
	{
		points[i][j].x = j;
		points[i][j].y = i;
		points[i][j].z = ft_atoi(arr[j]);
		points[i][j].is_last = 0;
		is_colorcheck(i, j, points, arr);
		j++;
	}
	points[i][--j].is_last = 1;
	j = 0;
	while (arr[j] != NULL)
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

t_fdf	*transform_into_struct(int fd, t_fdf *fdf, char *line)
{
	int		i;
	t_node	**points;

	points = malloc((fdf->height + 1) * sizeof(t_node *));
	if (points == NULL)
		exit (1);
	i = 0;
	while (line != NULL)
	{
		points[i] = malloc(fdf->width * sizeof(t_node));
		if (points[i] == NULL)
		{
			free_helper3(i, points);
			exit (1);
		}
		build_matrix(i++, fdf->width, points, line);
		free(line);
		line = get_next_line(fd);
	}
	points[i] = NULL;
	free(line);
	fdf->matrix = points;
	return (fdf);
}

t_node	**transform_into_iso(t_node **ptr, int col, int row)
{
	int		i;
	int		j;
	int32_t	iso_x;
	int32_t	iso_y;

	i = 0;
	j = 0;
	while (i < col)
	{
		while (j < row)
		{
			iso_x = ptr[i][j].x - ptr[i][j].y;
			iso_y = (ptr[i][j].x + ptr[i][j].y) / 2 - ptr[i][j].z;
			ptr[i][j].x = iso_x;
			ptr[i][j].y = iso_y;
			j++;
		}
		j = 0;
		i++;
	}
	return (ptr);
}
