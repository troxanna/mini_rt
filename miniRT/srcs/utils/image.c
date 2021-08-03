/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 08:14:46 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/23 00:31:40 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int			write_bmp_file_header(t_mlx *data, int fd)
{
	unsigned char	bmp[14];
	int				file_size;

	ft_bzero(bmp, 14);
	file_size = 54 + data->res_y * data->res_x * data->bits_per_pixel / 8;
	bmp[0] = 'B';
	bmp[1] = 'M';
	bmp[2] = (unsigned char)(file_size);
	bmp[3] = (unsigned char)(file_size >> 8);
	bmp[4] = (unsigned char)(file_size >> 16);
	bmp[5] = (unsigned char)(file_size >> 24);
	bmp[10] = (unsigned char)(54);
	if (write(fd, bmp, 14) < 0)
		return (0);
	return (1);
}

static int			write_bmp_info_header(int fd, t_mlx *data)
{
	unsigned char	bmp[40];

	ft_bzero(bmp, 40);
	bmp[0] = (unsigned char)(40);
	bmp[4] = (unsigned char)(data->res_x);
	bmp[5] = (unsigned char)(data->res_x >> 8);
	bmp[6] = (unsigned char)(data->res_x >> 16);
	bmp[7] = (unsigned char)(data->res_x >> 24);
	bmp[8] = (unsigned char)(-data->res_y);
	bmp[9] = (unsigned char)(-data->res_y >> 8);
	bmp[10] = (unsigned char)(-data->res_y >> 16);
	bmp[11] = (unsigned char)(-data->res_y >> 24);
	bmp[12] = (unsigned char)(1);
	bmp[14] = (unsigned char)(data->bits_per_pixel);
	if (write(fd, bmp, 40) < 0)
		return (0);
	return (1);
}

static int			write_image(int fd, t_mlx *data)
{
	int				i;
	int				block_size;

	i = 0;
	block_size = data->bits_per_pixel / 8 * data->res_x;
	while (i < data->res_y)
	{
		if (write(fd, &(data->addr[i * data->line_length]), block_size) < 0)
			return (0);
		i++;
	}
	return (1);
}

void				create_bmp(t_mlx *data)
{
	int				fd;

	fd = open("image.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0755);
	if (fd < 0)
		ft_error(4);
	if (!(write_bmp_file_header(data, fd)))
		ft_error(4);
	if (!write_bmp_info_header(fd, data))
		ft_error(4);
	if (!write_image(fd, data))
		ft_error(4);
	if (close(fd) < 0)
		ft_error(4);
}
