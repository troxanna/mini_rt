/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:34:05 by troxanna          #+#    #+#             */
/*   Updated: 2021/03/21 18:06:08 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


static void		screen_resolution_conversion(t_scene *scene, void *mlx_ptr)
{
	int			width_max;
	int			height_max;

	mlx_get_screen_size(mlx_ptr, &width_max, &height_max);
	if (scene->resolution->width > width_max)
		scene->resolution->width = width_max;
	if (scene->resolution->height > height_max)
		scene->resolution->height = height_max;
}

static int			parse_line(char *line, t_scene *scene)
{
	int			result_parser;

	if (line != NULL)
	{
		result_parser = parser_object_scene(line, scene);
		if (result_parser == -1)
			return (0);
	}
	free(line);
	return (1);
}

int				parser_rt(char *scene_rt, void *mlx_ptr, t_scene *scene)
{
	int			fd;
	int			result_gnl;
	char		*line;

	ft_init_scene(scene);
	line = NULL;
	if ((fd = open(scene_rt, O_RDONLY)) < 3)
		ft_error(3);
	while ((result_gnl = get_line(fd, &line)))
	{
		if (!(parse_line(line, scene)))
			return (0);
	}
	if (!(parse_line(line, scene)))
		return (0);
	close(fd);
	screen_resolution_conversion(scene, mlx_ptr);
	if (result_gnl == -1 || check_scene(scene) == -1)
		return (0);
	return (1);
}
