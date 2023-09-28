/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:48:43 by jmuller           #+#    #+#             */
/*   Updated: 2023/07/13 12:16:29 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_helper2(t_node **ptr, int col)
{
	int	i;

	i = 0;
	while (i < col)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

/* void	print_stack(char *stack, int stack_size)
{
	int	i;

	printf("Bit_String\n");
	i = 0;
	while (i < stack_size)
	{
		printf("%c", stack[i]);
		i++;
	}
	printf("\n");
	return ;
} */

void	print_matrix(t_node **points, int col, int row)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < row)
	{
		while (j < col)
		{
			printf("%d ", points[i][j].z);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
}

void	free_helper3(int i, t_node **points)
{
	while (i--)
		free(points[i]);
	free(points);
}
