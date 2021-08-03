/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 04:36:13 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 04:36:18 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void			get_params_sphere(t_object_params *o_p, t_vector *r_d,
									t_vector *r_o, t_sphere *s)
{
	t_vector		ray_dir_tmp;

	ray_dir_tmp = *r_d;
	scalars_mult_vectors(o_p->closest_t, &ray_dir_tmp);
	vector_addition(&(o_p->intersect_point), r_o, &ray_dir_tmp);
	vector_subtraction(&(o_p->norm), &(o_p->intersect_point), &(s->center));
	init_color(&(o_p->color), s->color.r, s->color.g, s->color.b);
}

static int			sphere_intersect(t_vector *ray_orig, t_vector *ray_dir,
													float *t, t_sphere *sphere)
{
	t_vector		cam_sphere;
	float			k[3];
	float			closet_t;

	closet_t = 65536;
	vector_subtraction(&cam_sphere, ray_orig, &(sphere->center));
	k[0] = vector_dot_products(ray_dir, ray_dir);
	k[1] = vector_dot_products(&cam_sphere, ray_dir) * 2;
	k[2] = vector_dot_products(&cam_sphere, &cam_sphere) -
										pow(sphere->radius, 2);
	closet_t = s_q(k[0], k[1], k[2], t);
	if (!(closet_t < 65536))
		return (0);
	if (closet_t == t[1])
		t[0] = t[1];
	return (1);
}

float				iterate_object_sphere(t_sphere *sphere,
	t_object_params *o_p, t_vector *ray_dir, t_vector *ray_orig)
{
	t_sphere		*ptr;
	t_sphere		*closest_sphere;
	float			r_t[2];

	closest_sphere = NULL;
	o_p->closest_t = 65536;
	ptr = sphere;
	while (ptr)
	{
		if ((sphere_intersect(ray_orig, ray_dir, r_t, ptr)))
			if (r_t[0] >= o_p->range[0] && r_t[0] < o_p->range[1]
										&& r_t[0] < o_p->closest_t)
			{
				o_p->closest_t = r_t[0];
				closest_sphere = ptr;
			}
		ptr = ptr->next;
	}
	if (closest_sphere)
	{
		get_params_sphere(o_p, ray_dir, ray_orig, closest_sphere);
		return (o_p->closest_t);
	}
	return (0);
}
