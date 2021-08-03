/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 01:29:08 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 01:29:13 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minirt.h"

static void				add_intensity_point_light(float *intensity,
									t_point_light *light, float dot_nl)
{
	intensity[0] = intensity[0] + light->brightness *
							light->color.r / 255 * (dot_nl);
	intensity[1] = intensity[1] + light->brightness *
							light->color.g / 255 * (dot_nl);
	intensity[2] = intensity[2] + light->brightness *
							light->color.b / 255 * (dot_nl);
}

static void				get_color_sum_point_lights(t_object_scene *obj_scene,
										t_object_params *o, float *intensity)
{
	t_point_light		*ptr;
	t_vector			l_ray;
	float				nl;
	int					tmp;

	ptr = obj_scene->point_light;
	while (ptr)
	{
		tmp = 0;
		vector_subtraction(&l_ray, &(ptr->point_light), &(o->intersect_point));
		if (angle_between_norm_and_light(&(o->norm), &l_ray))
		{
			if (o->flag == 1)
				reverse_normal(&(o->norm));
			tmp = (o->flag == 0) ? 1 : 0;
		}
		tmp = shadow_check(obj_scene, &l_ray, &(o->intersect_point));
		if (tmp == 0)
		{
			vector_normalize(&l_ray);
			nl = vector_dot_products(&(o->norm), &l_ray);
			add_intensity_point_light(intensity, ptr, nl);
		}
		ptr = ptr->next;
	}
}

static int				get_final_color(t_rgb *object_color, float i_lights[3])
{
	t_rgb				final_color;

	init_color(&final_color, object_color->r * i_lights[0],
		object_color->g * i_lights[1], object_color->b * i_lights[2]);
	if (final_color.r > 255)
		final_color.r = 255;
	if (final_color.g > 255)
		final_color.g = 255;
	if (final_color.b > 255)
		final_color.b = 255;
	return (create_trgb(0, final_color.r, final_color.g, final_color.b));
}

static void				negative_point_lights(float *intensity_sum_lights,
												float *intensity_ambient_light)
{
	intensity_sum_lights[0] = intensity_ambient_light[0];
	intensity_sum_lights[1] = intensity_ambient_light[1];
	intensity_sum_lights[2] = intensity_ambient_light[2];
}

int						get_light_point(t_object_scene *s,
										t_object_params *obj_params)
{
	float				i_sum_lights[3];
	float				i_ambient_light[3];
	float				i_point_lights[3];
	int					color;

	vector_normalize(&(obj_params->norm));
	i_point_lights[0] = 0;
	i_point_lights[1] = 0;
	i_point_lights[2] = 0;
	i_ambient_light[0] = s->amb_light->ambient * s->amb_light->color.r / 255;
	i_ambient_light[1] = s->amb_light->ambient * s->amb_light->color.g / 255;
	i_ambient_light[2] = s->amb_light->ambient * s->amb_light->color.b / 255;
	get_color_sum_point_lights(s, obj_params, i_point_lights);
	if (i_point_lights[0] < 0 || i_point_lights[1] < 0 || i_point_lights[2] < 0)
		negative_point_lights(i_sum_lights, i_ambient_light);
	else
	{
		i_sum_lights[0] = i_ambient_light[0] + i_point_lights[0];
		i_sum_lights[1] = i_ambient_light[1] + i_point_lights[1];
		i_sum_lights[2] = i_ambient_light[2] + i_point_lights[2];
	}
	color = get_final_color(&obj_params->color, i_sum_lights);
	return (color);
}
