/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 02:02:52 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/23 02:02:55 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void				my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char			*dst;

	dst = mlx->addr + (y * mlx->line_length + x * (mlx->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static int			mlx_action_window(int keycode, t_mlx *vars)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 48)
	{
		mlx_clear_window(vars->mlx, vars->win);
		switching_between_cameras(vars->scene, vars, vars->camera);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	}
	return (1);
}

static int			check_save(char *str)
{
	int				i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if ((i != 6 || str[i - 1] != 'e' || str[i - 2] != 'v'
				|| str[i - 3] != 'a' || str[i - 4] != 's'
					|| str[i - 5] != '-' || str[i - 6] != '-'))
		return (0);
	else
		return (1);
}

static void			mlx_init_p(t_mlx *mlx, t_scene *scene, t_camera *tmp_first)
{
	tmp_first = scene->camera;
	mlx->camera = tmp_first;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, scene->resolution->width,
								scene->resolution->height, "miniRT");
	mlx->img = mlx_new_image(mlx->mlx, scene->resolution->width,
										scene->resolution->height);
	mlx->addr = mlx_get_data_addr(mlx->img, &(mlx->bits_per_pixel),
								&(mlx->line_length), &(mlx->endian));
	mlx->scene = scene;
	mlx->res_x = scene->resolution->width;
	mlx->res_y = scene->resolution->height;
	mlx_hook(mlx->win, 17, 1L << 0, close_window, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, mlx_action_window, mlx);
}

int					main(int argc, char **argv)
{
	t_mlx			mlx;
	t_scene			scene;
	t_camera		*tmp_first;

	tmp_first = NULL;
	if (argc >= 2 && argc <= 3)
	{
		if (!(parser_rt(argv[1], mlx.mlx, &scene)))
			ft_error(2);
		mlx_init_p(&mlx, &scene, tmp_first);
		ray_tracing(&mlx, &scene);
		mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
		if (argc == 3)
			if (check_save(argv[2]))
				create_bmp(&mlx);
			else
				ft_error(4);
		else
			mlx_loop(mlx.mlx);
		return (1);
	}
	ft_error(5);
}
