/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_square.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 05:48:59 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 05:49:04 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void		get_params_square(t_vector *r_d, t_vector *r_o,
								float t1, t_object_params *o_p)
{
	t_vector	ray_dir_tmp;

	init_vector(&ray_dir_tmp, r_d->x, r_d->y, r_d->z);
	scalars_mult_vectors(t1, &ray_dir_tmp);
	vector_addition(&(o_p->intersect_point), r_o, &ray_dir_tmp);
}

static int		square_intersect(t_vector *r_o, t_vector *r_d,
								t_square *s, t_object_params *o_p)
{
	float		ab[2];
	float		t[2];
	t_vector	d[2];

	init_vector(&(o_p->norm), s->direction.x, s->direction.y, s->direction.z);
	vector_normalize(&(o_p->norm));
	vector_subtraction(&d[0], r_o, &(s->center_square));
	ab[0] = vector_dot_products(&d[0], &(o_p->norm));
	ab[1] = vector_dot_products(r_d, &(o_p->norm));
	if (ab[1] == 0 || (ab[0] < 0 && ab[1] < 0) || (ab[0] > 0 && ab[1] > 0))
		return (0);
	t[0] = -(ab[0] / ab[1]);
	get_params_square(r_d, r_o, t[0], o_p);
	vector_subtraction(&d[1], &(o_p->intersect_point), &(s->center_square));
	t[1] = s->side / 2;
	if (fabs(d[1].x) > t[1] || fabs(d[1].y) > t[1] || fabs(d[1].z) > t[1])
		return (0);
	if (t[0] > 0)
	{
		o_p->tmp_t[0] = t[0];
		return (1);
	}
	return (0);
}

float			iterate_object_square(t_square *square, t_object_params *o_p,
										t_vector *ray_dir, t_vector *ray_orig)
{
	t_square	*ptr;
	t_square	*c_sq;

	c_sq = NULL;
	o_p->closest_t = 65536;
	ptr = square;
	while (ptr)
	{
		if ((square_intersect(ray_orig, ray_dir, ptr, o_p)))
			if (o_p->tmp_t[0] >= o_p->range[0] && o_p->tmp_t[0] < o_p->range[1]
										&& o_p->tmp_t[0] < o_p->closest_t)
			{
				o_p->closest_t = o_p->tmp_t[0];
				c_sq = ptr;
			}
		ptr = ptr->next;
	}
	if (c_sq)
	{
		init_color(&o_p->color, c_sq->color.r, c_sq->color.g, c_sq->color.b);
		return (o_p->closest_t);
	}
	return (0);
}
