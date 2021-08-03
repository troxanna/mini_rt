/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 00:37:58 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/23 00:37:59 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void					init_shadow_range(t_object_params *o_p_tmp)
{
	o_p_tmp->range[0] = 0.000000001;
	o_p_tmp->range[1] = 0.9999;
}

int							shadow_check(t_object_scene *o_f,
								t_vector *l_ray, t_vector *i_p)
{
	t_object_params			o_p_tmp;
	float					closest_t;

	init_shadow_range(&o_p_tmp);
	if (o_f->sphere && (closest_t = iterate_object_sphere(o_f->sphere,
											&o_p_tmp, l_ray, i_p)))
		if (closest_t > o_p_tmp.range[0] && closest_t < o_p_tmp.range[1])
			return (1);
	if (o_f->triangle && (closest_t = iterate_object_triangle(o_f->triangle,
											&o_p_tmp, l_ray, i_p)))
		if (closest_t > o_p_tmp.range[0] && closest_t < o_p_tmp.range[1])
			return (1);
	if (o_f->square && (closest_t = iterate_object_square(o_f->square,
											&o_p_tmp, l_ray, i_p)))
		if (closest_t > o_p_tmp.range[0] && closest_t < o_p_tmp.range[1])
			return (1);
	if (o_f->cylinder && (closest_t = iterate_object_cylinder(o_f->cylinder,
												&o_p_tmp, l_ray, i_p)))
		if (closest_t > o_p_tmp.range[0] && closest_t < o_p_tmp.range[1])
			return (1);
	if (o_f->plane && (closest_t = iterate_object_plane(o_f->plane,
										&o_p_tmp, l_ray, i_p)))
		if (closest_t > o_p_tmp.range[0] && closest_t < o_p_tmp.range[1])
			return (1);
	return (0);
}
