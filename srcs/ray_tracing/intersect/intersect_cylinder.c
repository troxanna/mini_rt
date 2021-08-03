/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 05:52:06 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 05:52:09 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void			init_vectors(t_tmp *vectors, t_vector *r_d, t_vector *d)
{
	vectors->ray_dir = r_d;
	vectors->direction = d;
}

static void			get_coef(float *c, t_vector *r_d,
								t_cylinder *cy, t_vector *x)
{
	c[0] = vector_dot_products(r_d, r_d) -
				pow(vector_dot_products(r_d, &(cy->direction)), 2);
	c[1] = 2.0 * (vector_dot_products(r_d, x) -
				vector_dot_products(r_d, &(cy->direction))
				* vector_dot_products(x, &(cy->direction)));
	c[2] = vector_dot_products(x, x) -
			vector_dot_products(x, &(cy->direction)) *
		vector_dot_products(x, &(cy->direction)) - pow(cy->diameter / 2, 2);
}

static int			gnc(t_tmp *v, float t, float m, t_object_params *o_p)
{
	t_vector		tmp[4];

	init_vector(&tmp[0], v->ray_dir->x * t, v->ray_dir->y * t,
											v->ray_dir->z * t);
	vector_addition(&tmp[2], &tmp[0], &v->x);
	init_vector(&tmp[1], v->direction->x * m,
						v->direction->y * m, v->direction->z * m);
	vector_subtraction(&(o_p->norm), &tmp[2], &tmp[1]);
	vector_normalize(&(o_p->norm));
	o_p->tmp_t[0] = t;
	return (1);
}

static int			intersect_cylinder(t_vector *r_o, t_vector *r_d,
							t_cylinder *cy, t_object_params *o_p)
{
	float			tm[2];
	float			c[3];
	t_tmp			v;

	tm[0] = 65536;
	vector_normalize(&(cy->direction));
	vector_subtraction(&(v.x), r_o, &(cy->point_cylinder));
	get_coef(c, r_d, cy, &(v.x));
	if (!((tm[0] = s_q(c[0], c[1], c[2], &(o_p->tmp_t[0]))) < 65536))
		return (0);
	tm[1] = vector_dot_products(r_d, &(cy->direction)) * tm[0]
				+ vector_dot_products(&(v.x), &(cy->direction));
	init_vectors(&v, r_d, &(cy->direction));
	if (tm[1] >= 0.0 && tm[1] <= cy->height)
	{
		gnc(&v, tm[0], tm[1], o_p);
		return (1);
	}
	if (tm[0] == o_p->tmp_t[0])
		tm[0] = o_p->tmp_t[1];
	else if (tm[0] == o_p->tmp_t[1])
		tm[0] = o_p->tmp_t[0];
	tm[1] = vector_dot_products(r_d, &(cy->direction)) * tm[0] +
					vector_dot_products(&(v.x), &(cy->direction));
	return (tm[1] >= 0 && tm[1] <= cy->height) ? gnc(&v, tm[0], tm[1], o_p) : 0;
}

float				iterate_object_cylinder(t_cylinder *cy,
			t_object_params *o_p, t_vector *r_d, t_vector *r_o)
{
	t_cylinder		*ptr;
	t_cylinder		*c_cy;

	c_cy = NULL;
	o_p->closest_t = 65536;
	ptr = cy;
	while (ptr)
	{
		if ((intersect_cylinder(r_o, r_d, ptr, o_p)))
			if (o_p->tmp_t[0] >= o_p->range[0] && o_p->tmp_t[0] < o_p->range[1]
											&& o_p->tmp_t[0] < o_p->closest_t)
			{
				o_p->closest_t = o_p->tmp_t[0];
				c_cy = ptr;
			}
		ptr = ptr->next;
	}
	if (c_cy)
	{
		init_color(&o_p->color, c_cy->color.r, c_cy->color.g, c_cy->color.b);
		return (o_p->closest_t);
	}
	return (0);
}
