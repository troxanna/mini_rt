#include "../includes/minirt.h"

t_plane    *new_plane(t_vector point_plane, t_vector direction, t_rgb color)
{
    t_plane  *plane;

    if(!(plane = (t_plane *)malloc(sizeof(t_plane))))
        ft_error(1);
    plane->point_plane = point_plane;
    plane->direction = direction;
    plane->next = NULL;
    plane->color = color;
    return (plane);
}

void    add_plane(t_scene *scene, t_plane *next)
{
    t_plane    *ptr;

    ptr = scene->plane;
    if (scene->plane == NULL)
        scene->plane = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}