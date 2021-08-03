/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object_figure.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:12:10 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/20 23:47:29 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_sphere			*parser_sphere(char *line, int i, t_scene *scene)
{
	t_vector			sphere_center;
	t_rgb				color_sphere;
	float				diameter;
	float				*tmp;

	tmp = NULL;
	diameter = 0;
	while_parse(&i, line);
	if (!(ft_atovec(&sphere_center, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(tmp = ft_atof(line, &i, &diameter)) || diameter < 0)
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atorgb(&color_sphere, line, &i)))
		return (NULL);
	while (line[i++] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (NULL);
		i++;
	}
	add_sphere(scene, new_sphere(sphere_center, diameter / 2, color_sphere));
	return (scene->sphere);
}

static t_triangle		*parser_triangle(char *line, int i, t_scene *scene)
{
	t_vector			points[3];
	t_rgb				color_triangle;

	while_parse(&i, line);
	if (!(ft_atovec(points, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atovec(points + 1, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atovec(points + 2, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atorgb(&color_triangle, line, &i)))
		return (NULL);
	while (line[i++] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (NULL);
		i++;
	}
	add_triangle(scene, new_triangle(points[0], points[1], points[2],
														color_triangle));
	return (scene->triangle);
}

static t_plane			*parser_plane(char *line, int i, t_scene *scene)
{
	t_vector			point_plane;
	t_vector			direction;
	t_rgb				color_plane;

	while_parse(&i, line);
	if (!(ft_atovec(&point_plane, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atovec_norm(&direction, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atorgb(&color_plane, line, &i)))
		return (NULL);
	while (line[i++] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (NULL);
		i++;
	}
	add_plane(scene, new_plane(point_plane, direction, color_plane));
	return (scene->plane);
}

static t_square			*parser_square(char *line, int i,
									t_scene *scene, float *tmp)
{
	t_vector			square[2];
	float				side;
	t_rgb				color_square;

	while_parse(&i, line);
	if (!(ft_atovec(square, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atovec_norm(square + 1, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(tmp = ft_atof(line, &i, &side)) || side < 0)
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atorgb(&color_square, line, &i)))
		return (NULL);
	while (line[i++] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (NULL);
		i++;
	}
	add_square(scene, new_square(square[0], square[1], side, color_square));
	return (scene->square);
}

int						parser_object_figure(int i, char *line, t_scene *scene)
{
	float *tmp;

	tmp = NULL;
	if (line[i + 1] == 'p' && line[i++] == 's')
		return (!(scene->sphere = parser_sphere(line, ++i, scene)) ? -1 : i);
	else if (line[i + 1] == 'r' && line[i++] == 't')
		return (!(scene->triangle = parser_triangle(line, ++i, scene))
																? -1 : i);
	else if (line[i + 1] == 'l' && line[i++] == 'p')
		return (!(scene->plane = parser_plane(line, ++i, scene)) ? -1 : i);
	else if (line[i + 1] == 'q' && line[i++] == 's')
		return (!(scene->square = parser_square(line, ++i, scene, tmp)));
	else if (line[i + 1] == 'y' && line[i++] == 'c')
		return (!(scene->cylinder = parser_cylinder(line, ++i, scene, tmp))
																	? -1 : i);
	else
		return (-1);
}
