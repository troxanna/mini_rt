/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 05:33:07 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 05:33:10 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static int			triangle_intersect(t_triangle *tr, t_object_params *o_p,
										t_vector *r_d, t_vector *r_o)
{
	float			det[2];
	float			uv[2];
	t_vector		vec[4];

	vector_subtraction(&vec[0], &(tr->second_point), &(tr->first_point));
	vector_subtraction(&vec[1], &(tr->third_point), &(tr->first_point));
	vector_cross_products(&(o_p->norm), r_d, &vec[1]);
	det[0] = vector_dot_products(&vec[0], &(o_p->norm));
	if (det[0] < 0.00001 && det[0] > -0.00001)
		return (0);
	det[1] = 1 / det[0];
	vector_subtraction(&vec[2], r_o, &(tr->first_point));
	uv[0] = vector_dot_products(&vec[2], &(o_p->norm)) * det[1];
	if (uv[0] < 0 || uv[0] > 1)
		return (0);
	vector_cross_products(&vec[3], &vec[2], &vec[0]);
	uv[1] = vector_dot_products(r_d, &vec[3]) * det[1];
	if (uv[1] < 0 || (uv[0] + uv[1]) > 1)
		return (0);
	o_p->tmp_t[0] = vector_dot_products(&vec[1], &vec[3]) * det[1];
	if (o_p->tmp_t[0] > 0.001)
		return (1);
	else
		return (0);
}

float				iterate_object_triangle(t_triangle *t, t_object_params *o_p,
										t_vector *ray_dir, t_vector *ray_orig)
{
	t_triangle		*ptr;
	t_triangle		*c_tr;

	c_tr = NULL;
	o_p->closest_t = 65536;
	ptr = t;
	while (ptr)
	{
		if ((triangle_intersect(ptr, o_p, ray_dir, ray_orig)))
			if (o_p->tmp_t[0] >= o_p->range[0] && o_p->tmp_t[0] < o_p->range[1]
										&& o_p->tmp_t[0] < o_p->closest_t)
			{
				o_p->closest_t = o_p->tmp_t[0];
				c_tr = ptr;
			}
		ptr = ptr->next;
	}
	if (c_tr)
	{
		init_color(&o_p->color, c_tr->color.r, c_tr->color.g, c_tr->color.b);
		return (o_p->closest_t);
	}
	return (0);
}
