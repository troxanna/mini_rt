#include "../../includes/minirt.h"

t_resolution    *new_resolution(int width, int height)
{
    t_resolution *resolution;
    if(!(resolution = (t_resolution *)malloc(sizeof(t_resolution))))
        ft_error(1);
    resolution->width = width;
    resolution->height = height;
    return (resolution);
}

void                ft_init_scene(t_scene *scene)
{
    scene->amb_light = NULL;
    scene->camera = NULL;
    scene->point_light = NULL;
    scene->resolution = NULL;
    scene->sphere = NULL;
    scene->triangle = NULL;
    scene->plane = NULL;
    scene->cylinder = NULL;
    scene->square = NULL;
}


int		check_scene(t_scene *scene)
{
	if (scene->resolution == NULL)
		return (-1);
	else if (scene->amb_light == NULL)
		return (-1);
	else if (scene->camera == NULL)
		return (-1);
	return (0);
}