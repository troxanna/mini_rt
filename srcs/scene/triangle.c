#include "../includes/minirt.h"

t_triangle    *new_triangle(t_vector first_point, t_vector second_point, t_vector third_point, t_rgb color)
{
    t_triangle *triangle;

    if(!(triangle = (t_triangle *)malloc(sizeof(t_triangle))))
        ft_error(1);
    triangle->first_point = first_point;
    triangle->second_point = second_point;
    triangle->third_point = third_point;
    triangle->next = NULL;
    triangle->color = color;
    return (triangle);
}

void    add_triangle(t_scene *scene, t_triangle *next)
{
    t_triangle    *ptr;

    ptr = scene->triangle;
    if (scene->triangle == NULL)
        scene->triangle = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}