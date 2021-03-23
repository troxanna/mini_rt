#include "../includes/minirt.h"

t_cylinder    *new_cylinder(t_vector point_cylinder, t_vector direction, float diameter, float height, t_rgb color)
{
    t_cylinder  *cylinder;

    if(!(cylinder= (t_cylinder *)malloc(sizeof(t_cylinder))))
        exit(EXIT_FAILURE);
    cylinder->point_cylinder = point_cylinder;
    cylinder->direction = direction;
    cylinder->diameter = diameter;
    cylinder->height = height;
    cylinder->next = NULL;
    cylinder->color = color;
    return (cylinder);
}

void    add_cylinder(t_scene *scene, t_cylinder *next)
{
    t_cylinder    *ptr;

    ptr = scene->cylinder;
    if (scene->cylinder == NULL)
        scene->cylinder = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}