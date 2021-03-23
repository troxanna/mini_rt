#include "../includes/minirt.h"

t_square        *new_square(t_vector center_square, t_vector direction, float side, t_rgb color)
{
    t_square    *square;

    if(!(square = (t_square *)malloc(sizeof(t_square))))
        ft_error(1);
    square->center_square = center_square;
    square->direction = direction;
    square->side = side;
    square->next = NULL;
    square->color = color;
    return (square);
}

void    add_square(t_scene *scene, t_square *next)
{
    t_square    *ptr;

    ptr = scene->square;
    if (scene->square == NULL)
        scene->square = next;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = next;
	}
}