#include "../../../includes/minirt.h"

float   *intersect_object(t_object_params *object_params, t_object_figure *object_figure, t_vector *ray_dir)
{
    //float       t;
    float       range_t[3];
    float       *tmp;
    t_vector    ray_dir_tmp;
    t_object_params object_params_tmp;
    //t = 0;
    range_t[0] = 0;
    range_t[1] = 1;
    range_t[2] = 65536;

    tmp = NULL;
    if (object_figure->sphere && (iterate_object_sphere(object_figure->sphere, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    {
        if (tmp == NULL || (tmp && *tmp > range_t[0]))
        {
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->flag = 0;
            tmp = range_t;
        }
    }
    if (object_figure->triangle && (iterate_object_triangle(object_figure->triangle, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    {
        if (tmp == NULL || (tmp && *tmp > range_t[0]))
        {
            //printf("test");
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->intersect_point = object_params_tmp.intersect_point;
            object_params->flag = 1;
            tmp = range_t;
        }
    }
    if (object_figure->square && (iterate_object_square(object_figure->square, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    {
        if (tmp == NULL || (tmp && *tmp > range_t[0]))
        {
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->intersect_point = object_params_tmp.intersect_point;
            object_params->flag = 1;
            tmp = range_t;
        }
    }
    if (object_figure->cylinder && (iterate_object_cylinder(object_figure->cylinder, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    {
        if (tmp == NULL || (tmp && *tmp > range_t[0]))
        {
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->intersect_point = object_params_tmp.intersect_point;
            object_params->flag = 0;
            tmp = range_t;
        }
    }
    if ((iterate_object_plane(object_figure->plane, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    {
        if (tmp == NULL || (tmp && *tmp > range_t[0]))
        {
            //printf("%s\n", "test");
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->flag = 1;
            tmp = range_t;
        }
    }
    if (tmp != NULL)
    {
        ray_dir_tmp = *ray_dir;
        scalars_mult_vectors(*tmp, &ray_dir_tmp);
        vector_addition(&(object_params->intersect_point), object_figure->ray_orig, &ray_dir_tmp);
    }
    return (tmp);
}