/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:26:10 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/20 19:34:13 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void			init_vector(t_vector *result,
							float x, float y, float z)
{
	result->x = x;
	result->y = y;
	result->z = z;
}

t_vector		*new_vector(float x, float y, float z)
{
	t_vector	*result;

	if (!(result = malloc(sizeof(t_vector))))
		ft_error(1);
	result->x = x;
	result->y = y;
	result->z = z;
	return (result);
}

void			vector_addition(t_vector *result,
							t_vector *v1, t_vector *v2)
{
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
}

void			vector_subtraction(t_vector *result,
							t_vector *v1, t_vector *v2)
{
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
}

float			vector_length(t_vector *v)
{
	float		len;

	if (!(len = sqrt((v->x * v->x) + (v->y * v->y) +
										(v->z * v->z))))
		ft_error(1);
	return (len);
}
