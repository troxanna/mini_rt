/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:32:09 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/20 19:47:18 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			vector_normalize(t_vector *v)
{
	float len;

	len = vector_length(v);
	v->x = v->x / len;
	v->y = v->y / len;
	v->z = v->z / len;
}

void			scalars_mult_vectors(float scalar,
										t_vector *vector)
{
	vector->x = vector->x * scalar;
	vector->y = vector->y * scalar;
	vector->z = vector->z * scalar;
}

float			vector_dot_products(t_vector *v1, t_vector *v2)
{
	float result;

	result = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
	return (result);
}

void			vector_cross_products(t_vector *result,
									t_vector *v1, t_vector *v2)
{
	result->x = (v1->y * v2->z) - (v1->z * v2->y);
	result->y = (v1->z * v2->x) - (v1->x * v2->z);
	result->z = (v1->x * v2->y) - (v1->y * v2->x);
}

t_vector		*matrix_to_world(t_vector *ray_dir,
										t_vector *camera_dir)
{
	t_vector	tmp_vector;
	t_vector	vector_right;
	t_vector	vector_up;
	t_vector	*result;

	vector_normalize(camera_dir);
	init_vector(&tmp_vector, 0, 1, 0);
	result = new_vector(0, 0, 0);
	vector_cross_products(&vector_right, &tmp_vector, camera_dir);
	vector_cross_products(&vector_up, camera_dir, &vector_right);
	result->x = ray_dir->x * vector_right.x + ray_dir->y * vector_right.y
												+ ray_dir->z * vector_right.z;
	result->y = ray_dir->x * vector_up.x + ray_dir->y * vector_up.y
													+ ray_dir->z * vector_up.z;
	result->z = ray_dir->x * camera_dir->x + ray_dir->y * camera_dir->y
												+ ray_dir->z * camera_dir->z;
	return (result);
}
