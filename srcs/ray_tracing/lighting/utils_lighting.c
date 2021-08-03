/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lighting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 00:41:47 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/23 00:41:48 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

int					angle_between_norm_and_light(t_vector *norm,
												t_vector *l_ray)
{
	float			dot;

	dot = vector_dot_products(norm, l_ray);
	if (dot >= 0)
		return (0);
	else
		return (1);
}

void				reverse_normal(t_vector *norm)
{
	if (norm->x < 0)
		norm->x = norm->x * (-1);
	if (norm->y < 0)
		norm->y = norm->y * (-1);
	if (norm->z < 0)
		norm->z = norm->z * (-1);
}
