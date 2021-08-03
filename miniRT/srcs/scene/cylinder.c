/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 00:44:55 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 00:45:00 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_cylinder			*new_cylinder(t_vector point_cylinder, t_vector direction,
														float *dh, t_rgb color)
{
	t_cylinder		*cylinder;

	if (!(cylinder = (t_cylinder *)malloc(sizeof(t_cylinder))))
		ft_error(1);
	cylinder->point_cylinder = point_cylinder;
	cylinder->direction = direction;
	cylinder->diameter = dh[0];
	cylinder->height = dh[1];
	cylinder->next = NULL;
	cylinder->color = color;
	return (cylinder);
}

void				add_cylinder(t_scene *scene, t_cylinder *next)
{
	t_cylinder		*ptr;

	ptr = scene->cylinder;
	if (scene->cylinder == NULL)
		scene->cylinder = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}
