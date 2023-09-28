/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:39:03 by jmuller           #+#    #+#             */
/*   Updated: 2023/08/28 11:47:52 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../../../get_next_line/get_next_line.h"
# include "../../../libft/libft.h"
# include "../../../printf/include/ft_printf.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../MLX42/include/MLX42/MLX42_Int.h"
# include <errno.h>
# include "../MLX42/include/MLX42/MLX42_Input.h"
# include <limits.h>
# include <math.h>

typedef struct s_val
{
	int	step_x;
	int	step_y;
	int	err1;
	int	err2;
	int	dx;
	int	dy;
}	t_val;

typedef struct s_node
{
	int			x;
	int			y;
	int			z;
	int			is_last;
	long long	is_color;
}	t_node;

typedef struct s_fdf
{
	t_node				**matrix;
	t_val				val;
	int					height;
	int					width;
	int					win_x;
	int					win_y;
	int					z_scale;
	int					scale;
	int					is_isometric;
	double				angle;
	int					shift_x;
	int					shift_y;
	long long			color;
	mlx_t				*mlx_key;
	mlx_image_t			*img_key;

}	t_fdf;

//              Utils
void			print_matrix(t_node **points, int col, int row);
void			free_helper2(t_node **ptr, int col);
void			free_helper(char *line, char **arr, int col);
void			print_stack(char *stack, int stack_size);
void			free_helper3(int i, t_node **points);
long long		hex_to_dec(char *str);
void			ft_error(int errnum);
//int				ft_atoh(const char *nptr);

// ....Create Matrix
int				nbr_of_rows(int fd);
int				nbr_of_columns(char *line);
void			build_matrix(int i, int col, t_node **points, char *line);
t_node			**transform_into_iso(t_node **ptr, int col, int row);
t_fdf			*transform_into_struct(int fd, t_fdf *fdf, char *line);
void			shift_to_center(t_node *p1, t_node *p2, t_fdf *fdf);
void			make_isometric(t_node *node, double angle);
void			set_zoom(t_node *p1, t_node *p2, t_fdf *fdf);
void			is_colorcheck(int i, int j, t_node **points, char **arr);
void			set_color(t_node *p1, t_node *p2, t_fdf *fdf);

char			**ft_split2(char const *s, char c);
int				ft_splitlen(char const *s, char c, int flag);
char			**ft_free(char **array, int j);

// ... Draw Stuff

void			draw(void *fdf);
void			draw_line(mlx_image_t *img, t_node pt1, t_node pt2, t_fdf *fdf);

// ... Initialize Stuff
void			default_graphics_setting(t_fdf *fdf);

// ... Key Stuff

void			key_hook(mlx_key_data_t keydata, void *para);

// ... Draw Menu
void			draw_menu(t_fdf *fdf);

//    Error Handling
void			ft_error(int errnum);

#endif