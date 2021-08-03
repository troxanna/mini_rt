/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 00:42:48 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 00:42:49 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_camera			*new_camera(t_vector origin, t_vector direction, float fov)
{
	t_camera		*camera;

	if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
		ft_error(1);
	camera->origin = origin;
	camera->direction = direction;
	camera->fov = fov;
	camera->next = NULL;
	return (camera);
}

void				add_camera(t_scene *scene, t_camera *next)
{
	t_camera		*ptr;

	ptr = scene->camera;
	if (scene->camera == NULL)
		scene->camera = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}

void				switching_between_cameras(t_scene *scene,
							t_mlx *mlx, t_camera *camera_first)
{
	if (scene->camera->next == NULL)
		scene->camera = camera_first;
	else
		scene->camera = scene->camera->next;
	ray_tracing(mlx, scene);
}
