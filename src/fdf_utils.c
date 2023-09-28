/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmuller <jmuller@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:13:29 by jmuller           #+#    #+#             */
/*   Updated: 2023/07/13 12:16:33 by jmuller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include "../include/fdf.h"
#include "MLX42/MLX42.h"

/* the added term in the result accounts for the alpha channel*/
long long	hex_to_dec(char *str)
{
	int	i;
	int	res;
	int	digit;

	res = 0;
	i = 0;
	digit = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			digit = str[i] - '0';
		}
		else
		{
			digit = str[i] - 'A' + 10;
		}
		res = res * 16 + digit;
		i++;
	}
	return (res * 256 + 255);
}

void	ft_error(int errnum)
{
	ft_printf("%s\n", strerror(errnum));
	exit (1);
}

int	nbr_of_rows(int fd)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	free(line);
	i = 0;
	while (line)
	{
		line = get_next_line(fd);
		free(line);
		i++;
	}
	return (i);
}

int	nbr_of_columns(char *line)
{
	int		col;
	int		fd;
	int		i;

	i = 0;
	col = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
		{
			while (line[i] == ' ')
				i++;
			col++;
		}
		else
			i++;
	}
	return (col);
}
