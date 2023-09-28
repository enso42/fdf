/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:03:30 by jmuller           #+#    #+#             */
/*   Updated: 2023/08/28 16:15:59 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

t_fdf	*matrix_read_out(int fd, char *argv[])
{
	char		*line;
	t_node		**matrix;
	t_fdf		*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (fdf == NULL)
		exit(1);
	line = get_next_line(fd);
	fdf->width = nbr_of_columns(line);
	if (!fdf->width || fdf->width < 2)
		ft_error(EIO);
	free(line);
	fdf->height = nbr_of_rows(fd) + 1;
	close(fd);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		ft_error(ENOENT);
	line = get_next_line(fd);
	fdf = transform_into_struct(fd, fdf, line);
	return (fdf);
}

void	initialize_graphics(t_fdf *fdf)
{
	default_graphics_setting(fdf);
	fdf->mlx_key = mlx_init(fdf->win_x, fdf->win_y, "FDF", true);
	fdf->img_key = mlx_new_image(fdf->mlx_key, fdf->win_x, fdf->win_y);
}

void	free_matrix(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->height)
	{
		free(fdf->matrix[i++]);
	}
	free(fdf->matrix);
	free(fdf);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;
	int		fd;

	fd = 0;
	if (argc != 2)
		ft_error(EBADF);
	fd = open(argv[1], O_RDONLY);
	if (fd <= 0)
		ft_error(ENOENT);
	fdf = matrix_read_out(fd, argv);
	initialize_graphics(fdf);
	mlx_image_to_window(fdf->mlx_key, fdf->img_key, 0, 0);
	draw_menu(fdf);
	mlx_loop_hook(fdf->mlx_key, draw, fdf);
	mlx_key_hook(fdf->mlx_key, key_hook, fdf);
	mlx_loop(fdf->mlx_key);
	mlx_terminate(fdf->mlx_key);
	free_matrix(fdf);
	return (EXIT_SUCCESS);
}
