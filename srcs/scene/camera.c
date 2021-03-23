#include "../includes/minirt.h"

t_camera    *new_camera(t_vector origin, t_vector direction, float fov)
{
    t_camera *camera;

    if (!(camera = (t_camera *)malloc(sizeof(t_camera))))
        exit(EXIT_FAILURE);
    camera->origin = origin;
    camera->direction = direction;
    camera->fov = fov;
    camera->next = NULL;
    return (camera);
}

void    add_camera(t_scene *scene, t_camera *next)
{
    t_camera    *ptr;

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