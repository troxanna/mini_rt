/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 01:20:04 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 01:20:09 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_sphere		*new_sphere(t_vector center, float radius, t_rgb color)
{
	t_sphere	*sphere;

	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		ft_error(1);
	sphere->center = center;
	sphere->radius = radius;
	sphere->next = NULL;
	sphere->color = color;
	return (sphere);
}

void			add_sphere(t_scene *scene, t_sphere *next)
{
	t_sphere	*ptr;

	ptr = scene->sphere;
	if (scene->sphere == NULL)
		scene->sphere = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}
