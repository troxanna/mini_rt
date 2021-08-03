/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 04:58:01 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 04:58:04 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void		get_params_sphere(t_object_params *o_p, t_plane *p)
{
	init_color(&o_p->color, p->color.r, p->color.g, p->color.b);
	init_vector(&o_p->norm, p->direction.x, p->direction.y, p->direction.z);
}

static int		intersect_plane(t_vector *ray_orig,
			t_vector *ray_dir, float *t, t_plane *plane)
{
	float		d;
	t_vector	n;

	init_vector(&n, plane->direction.x, plane->direction.y, plane->direction.z);
	d = -vector_dot_products(&(plane->point_plane), &n);
	t[0] = -((vector_dot_products(ray_orig, &n) + d) /
						(vector_dot_products(ray_dir, &n)));
	if (t >= 0)
		return (1);
	return (0);
}

float			iterate_object_plane(t_plane *plane, t_object_params *o_p,
												t_vector *r_d, t_vector *r_o)
{
	t_plane		*ptr;
	float		r_t[2];
	t_plane		*closest_plane;

	o_p->closest_t = 65536;
	closest_plane = NULL;
	ptr = plane;
	while (ptr)
	{
		if ((intersect_plane(r_o, r_d, r_t, ptr)))
			if (r_t[0] >= o_p->range[0] && r_t[0] < o_p->range[1]
										&& r_t[0] < o_p->closest_t)
			{
				o_p->closest_t = r_t[0];
				closest_plane = ptr;
			}
		ptr = ptr->next;
	}
	if (closest_plane)
	{
		get_params_sphere(o_p, closest_plane);
		return (o_p->closest_t);
	}
	return (0);
}
