#include "../../../includes/minirt.h"

float   *intersect_object(t_object_params *object_params, t_object_figure *object_figure, t_vector *ray_dir)
{
    float       t;
    float       *tmp;
    t_vector    ray_dir_tmp;

    t = 0;
    tmp = NULL;

    if ((iterate_object_sphere(object_figure->sphere, object_params, ray_dir, object_figure->ray_orig, &t)) >= 0)
        tmp = &t;
    if ((iterate_object_plane(object_figure->plane, object_params, ray_dir, object_figure->ray_orig, &t)) >= 0)
    {
        if ((tmp && *tmp > t) || !tmp)
            tmp = &t;
    }
    if (tmp)
    {
        ray_dir_tmp = *ray_dir;
        scalars_mult_vectors(*tmp, &ray_dir_tmp);
        vector_addition(&(object_params->intersect_point), object_figure->ray_orig, &ray_dir_tmp);
    }
    return (tmp);
}