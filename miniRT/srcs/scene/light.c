/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 01:14:10 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 01:14:14 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_amb_light			*new_ambient_light(float bright_ambient, t_rgb color)
{
	t_amb_light		*amb_light;

	if (!(amb_light = (t_amb_light *)malloc(sizeof(t_amb_light))))
		ft_error(1);
	amb_light->ambient = bright_ambient;
	amb_light->color.r = color.r;
	amb_light->color.g = color.g;
	amb_light->color.b = color.b;
	return (amb_light);
}

t_point_light		*new_light(t_vector light_point, float bright_light,
															t_rgb color)
{
	t_point_light		*point_light;

	if (!(point_light = (t_point_light *)malloc(sizeof(t_point_light))))
		ft_error(1);
	point_light->point_light = light_point;
	point_light->brightness = bright_light;
	point_light->color = color;
	point_light->next = NULL;
	return (point_light);
}

void				add_point_light(t_scene *scene, t_point_light *next)
{
	t_point_light	*ptr;

	ptr = scene->point_light;
	if (scene->point_light == NULL)
		scene->point_light = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}
