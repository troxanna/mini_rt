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

// t_scene    *new_scene(t_object *object)
// {
//     t_scene *scene;

//     if(!(scene = (t_scene *)malloc(sizeof(t_scene))))
//         exit(1);
//     scene->width = object->resolution->width;
//     scene->height = object->resolution->height;
//     scene->object = object;
//     return (scene);
// }
