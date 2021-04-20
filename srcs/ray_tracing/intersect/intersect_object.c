#include "../../../includes/minirt.h"

float   intersect_object(t_object_params *object_params, t_object_figure *object_figure, t_vector *ray_dir)
{
    //float       t;
    //float       range_t[3];
    float       tmp;
    tmp = 65536;
    float       closest_t;
    t_vector    ray_dir_tmp;
    t_object_params object_params_tmp;
    //t = 0;
    // range_t[0] = 0;
    // range_t[1] = 1;
    // range_t[2] = 65536;

    if (object_figure->sphere && (closest_t = iterate_object_sphere(object_figure->sphere, &object_params_tmp, ray_dir, object_figure->ray_orig)))
    {
        tmp = closest_t;

        object_params->color = object_params_tmp.color;
        object_params->norm = object_params_tmp.norm;
        object_params->flag = 0;
        // if (tmp == NULL || (tmp && *tmp > range_t[0]))
        // {
        //     object_params->color = object_params_tmp.color;
        //     object_params->norm = object_params_tmp.norm;
        //     object_params->flag = 0;
        //     tmp = range_t;
        // }
    }
    if (object_figure->triangle && (closest_t = iterate_object_triangle(object_figure->triangle, &object_params_tmp, ray_dir, object_figure->ray_orig)))
    {
        if (closest_t < tmp)
        {
            tmp = closest_t;
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->flag = 1;
        }
    }
    if (object_figure->plane && (closest_t = iterate_object_plane(object_figure->plane, &object_params_tmp, ray_dir, object_figure->ray_orig)))
    {
        if (closest_t < tmp)
        {
            tmp = closest_t;
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->flag = 1;
        }
    }
    if (object_figure->square && (closest_t = iterate_object_square(object_figure->square, &object_params_tmp, ray_dir, object_figure->ray_orig)))
    {
        if (closest_t < tmp)
        {
            tmp = closest_t;
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->flag = 1;
        }
    }
    if (object_figure->cylinder && (closest_t = iterate_object_cylinder(object_figure->cylinder, &object_params_tmp, ray_dir, object_figure->ray_orig)))
    {
        if (closest_t < tmp)
        {
            tmp = closest_t;
            object_params->color = object_params_tmp.color;
            object_params->norm = object_params_tmp.norm;
            object_params->flag = 0;
        }
    }
    // if (object_figure->triangle && (iterate_object_triangle(object_figure->triangle, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    // {
    //     if (tmp == NULL || (tmp && *tmp > range_t[0]))
    //     {
    //         //printf("test");
    //         object_params->color = object_params_tmp.color;
    //         object_params->norm = object_params_tmp.norm;
    //         object_params->intersect_point = object_params_tmp.intersect_point;
    //         object_params->flag = 1;
    //         tmp = range_t;
    //     }
    // }
    // if (object_figure->square && (iterate_object_square(object_figure->square, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    // {
    //     if (tmp == NULL || (tmp && *tmp > range_t[0]))
    //     {
    //         object_params->color = object_params_tmp.color;
    //         object_params->norm = object_params_tmp.norm;
    //         object_params->intersect_point = object_params_tmp.intersect_point;
    //         object_params->flag = 1;
    //         tmp = range_t;
    //     }
    // }
    // if (object_figure->cylinder && (iterate_object_cylinder(object_figure->cylinder, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    // {
    //     if (tmp == NULL || (tmp && *tmp > range_t[0]))
    //     {
    //         object_params->color = object_params_tmp.color;
    //         object_params->norm = object_params_tmp.norm;
    //         object_params->intersect_point = object_params_tmp.intersect_point;
    //         object_params->flag = 0;
    //         tmp = range_t;
    //     }
    // }
    // if ((iterate_object_plane(object_figure->plane, &object_params_tmp, ray_dir, object_figure->ray_orig, range_t)))
    // {
    //     if (tmp == NULL || (tmp && *tmp > range_t[0]))
    //     {
    //         //printf("%s\n", "test");
    //         object_params->color = object_params_tmp.color;
    //         object_params->norm = object_params_tmp.norm;
    //         object_params->flag = 1;
    //         tmp = range_t;
    //     }
    // }
    if (tmp != 65536)
    {
        t_vector tmp_vec;
        init_vector(&ray_dir_tmp, ray_dir->x, ray_dir->y, ray_dir->z);
        //if (object_params->flag == 1)
            tmp = tmp * 0.9708;
        //tmp = tmp * 0.9708;
        scalars_mult_vectors(tmp, &ray_dir_tmp);
        vector_addition(&(object_params->intersect_point), object_figure->ray_orig, &ray_dir_tmp);
        // if (object_params->flag == 1)
        // {
        //     init_vector(&tmp_vec, object_params->norm.x * 0.01, object_params->norm.y * 0.01, object_params->norm.z * 0.01);
        //     vector_addition(&(object_params->intersect_point), &(object_params->intersect_point), &tmp_vec);
        // }
        return (1);
    }
    return (0);
}