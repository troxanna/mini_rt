/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 02:53:11 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 04:02:56 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void				set_params_flat(t_object_params *obj,
								t_vector norm, t_rgb color, float t)
{
	obj->color = color;
	obj->norm = norm;
	obj->flag = 1;
	obj->tmp_t[0] = t;
}

static void				set_params_volume(t_object_params *obj,
								t_vector norm, t_rgb color, float t)
{
	obj->color = color;
	obj->norm = norm;
	obj->flag = 0;
	obj->tmp_t[0] = t;
}

static int				s_i_p(t_vector *ray_dir,
							t_object_params *obj, t_vector *ray_orig)
{
	t_vector r_tmp;

	init_vector(&r_tmp, ray_dir->x, ray_dir->y, ray_dir->z);
	obj->tmp_t[0] = obj->tmp_t[0] * 0.93;
	scalars_mult_vectors(obj->tmp_t[0], &r_tmp);
	vector_addition(&(obj->intersect_point), ray_orig, &r_tmp);
	return (1);
}

float					intersect_object(t_object_params *o_p,
						t_object_scene *o_f, t_vector *ray_dir)
{
	t_object_params		o_p_tmp;

	o_p->tmp_t[0] = 65536;
	o_p_tmp.range[0] = 1;
	o_p_tmp.range[1] = 65536;
	if (o_f->sphere && (o_p->closest_t = iterate_object_sphere(o_f->sphere,
										&o_p_tmp, ray_dir, o_f->ray_orig)))
		set_params_volume(o_p, o_p_tmp.norm, o_p_tmp.color, o_p->closest_t);
	if (o_f->triangle && (o_p->closest_t =
	iterate_object_triangle(o_f->triangle, &o_p_tmp, ray_dir, o_f->ray_orig)))
		if (o_p->closest_t < o_p->tmp_t[0])
			set_params_flat(o_p, o_p_tmp.norm, o_p_tmp.color, o_p->closest_t);
	if (o_f->plane && (o_p->closest_t = iterate_object_plane(o_f->plane,
									&o_p_tmp, ray_dir, o_f->ray_orig)))
		if (o_p->closest_t < o_p->tmp_t[0])
			set_params_flat(o_p, o_p_tmp.norm, o_p_tmp.color, o_p->closest_t);
	if (o_f->square && (o_p->closest_t = iterate_object_square(o_f->square,
										&o_p_tmp, ray_dir, o_f->ray_orig)))
		if (o_p->closest_t < o_p->tmp_t[0])
			set_params_flat(o_p, o_p_tmp.norm, o_p_tmp.color, o_p->closest_t);
	if (o_f->cylinder && (o_p->closest_t =
	iterate_object_cylinder(o_f->cylinder, &o_p_tmp, ray_dir, o_f->ray_orig)))
		if (o_p->closest_t < o_p->tmp_t[0])
			set_params_volume(o_p, o_p_tmp.norm, o_p_tmp.color, o_p->closest_t);
	return (o_p->tmp_t[0] != 65536) ? (s_i_p(ray_dir, o_p, o_f->ray_orig)) : 0;
}
