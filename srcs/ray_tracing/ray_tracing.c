/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 02:36:39 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 02:50:04 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void				init_ray_tracing(t_scene *scene,
		t_object_scene *object_scene)
{
	object_scene->plane = scene->plane;
	object_scene->sphere = scene->sphere;
	object_scene->triangle = scene->triangle;
	object_scene->square = scene->square;
	object_scene->cylinder = scene->cylinder;
	object_scene->ray_orig = &(scene->camera->origin);
	object_scene->amb_light = scene->amb_light;
	object_scene->point_light = scene->point_light;
}

static t_vector			*new_ray(t_scene *scene, int pixel_x, int pixel_y)
{
	t_vector			*ray;
	float				ray_x;
	float				ray_y;
	float				scale;
	t_vector			tmp_ray;

	scale = tan(scene->camera->fov / 2 * M_PI / 180);
	ray_x = (2 * ((pixel_x + 0.5) /
			(float)scene->resolution->width) - 1) * scale *
		((float)scene->resolution->width / (float)scene->resolution->height);
	ray_y = (1 - 2 * ((pixel_y + 0.5) /
		(float)scene->resolution->height)) * scale;
	init_vector(&tmp_ray, ray_x, ray_y, -1);
	ray = matrix_to_world(&tmp_ray, &(scene->camera->direction));
	return (ray);
}

void					ray_tracing(t_mlx *mlx, t_scene *scene)
{
	t_object_params		object_params;
	t_object_scene		object_scene;
	t_vector			*ray_dir;
	float				pixel[2];
	int					color;

	init_ray_tracing(scene, &object_scene);
	pixel[1] = 0;
	while (pixel[1] < scene->resolution->height)
	{
		pixel[0] = 0;
		while (pixel[0] < scene->resolution->width)
		{
			ray_dir = new_ray(scene, pixel[0], pixel[1]);
			if (intersect_object(&object_params, &object_scene, ray_dir))
				color = get_light_point(&object_scene, &object_params);
			else
				color = create_trgb(0, 0, 0, 0);
			free(ray_dir);
			my_mlx_pixel_put(mlx, pixel[0], pixel[1], color);
			pixel[0]++;
		}
		pixel[1]++;
	}
}
