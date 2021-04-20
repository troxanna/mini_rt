#include "../../../includes/minirt.h"

// static void     get_object_params_plane(t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float closest_t, t_plane *plane)
// {
//     t_vector    ray_dir_tmp;

//     ray_dir_tmp = *ray_dir;
//     scalars_mult_vectors(closest_t, &ray_dir_tmp);
//     vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
//     vector_subtraction(&(object_params->norm), &(object_params->intersect_point), &(sphere->center));
//     init_color(&(object_params->color), sphere->color.r, sphere->color.g, sphere->color.b);
// }

// static int     intersect_plane(t_vector *ray_orig, t_vector *ray_dir, float *t, t_plane *plane)
// {
//     float       denom;
//     float y;
//     t_vector    LP;
//     vector_normalize(&(plane->direction));
//     vector_normalize(ray_dir);
//     //vector_normalize(plane->point_plane);
//     denom = vector_dot_products(ray_dir, &(plane->direction));
//     //printf("%f\n", denom);
//     if (denom > 0.001)
//     {
//         vector_subtraction(&LP, &(plane->point_plane), ray_orig);
//         t[0] = vector_dot_products(&LP, &(plane->direction));
//         //return (1);
//         if (t[0] >= 0)
//         {
//             return (1);
//         }
//         else
//             return (0);
//    }
//    return (0);
// }

// static int     intersect_plane(t_vector *ray_orig, t_vector *ray_dir, float *t, t_plane *plane)
// {
//     float       denom;
//     float y;
//     t_vector    LP;
//     t_vector    norm;
//     init_vector(&norm, plane->direction.x * (-1), plane->direction.y * (-1), plane->direction.z * (-1));
//     vector_normalize(&(norm));
//     vector_normalize(&(plane->direction));
//     //vector_normalize(plane->point_plane);
//     denom = vector_dot_products(&(plane->point_plane), &(norm));
//     //printf("%f\n", denom);
//     if (denom > 0.000001)
//     {
//         t[0] = -(denom + vector_dot_products(ray_orig, &(plane->direction))) / vector_dot_products(ray_dir, &(plane->direction));
//         // vector_subtraction(&LP, &(plane->point_plane), ray_orig);
//         // t[0] = vector_dot_products(&LP, &(plane->direction));
//         //return (1);
//         if (t[0] >= 0)
//         {
//             return (1);
//         }
//         else
//             return (0);
//    }
//    return (0);
// }

static int intersect_plane(t_vector *ray_orig, t_vector *ray_dir, float *t, t_plane *plane) 
{
    float       d;
    t_vector    n;

    init_vector(&n, plane->direction.x, plane->direction.y, plane->direction.z);
    //vector_normalize(&n);
    //vector_normalize(ray_dir);
    d = -vector_dot_products(&(plane->point_plane), &n);
    //printf("%d\n", *t);
    // n = vec_normalize(n);
    // l = vec_normalize(l);
    t[0] = -((vector_dot_products(ray_orig, &n) + d) / (vector_dot_products(ray_dir, &n)));
    //printf("%f\n", *t);
    if (t >= 0)
        return (1);
    return (0);
}

float           iterate_object_plane(t_plane *plane, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig)
{
    t_plane    *ptr;
    float   range_t[3];
    float       closest_t;
    t_plane    *closest_plane;

    range_t[0] = 0;
    range_t[1] = 0.0000001;
    range_t[2] = 65536;
    closest_plane = NULL;
    closest_t = 65536;
    ptr = plane;
    while (ptr)
    {
        if ((intersect_plane(ray_orig, ray_dir, &range_t[0], ptr)))
        {
            if (range_t[0] >= range_t[1] && range_t[0] < range_t[2] && range_t[0] < closest_t)
            {
                closest_t = range_t[0];
                closest_plane = ptr;
            }
        }
        ptr = ptr->next;
    }
    //проверить возвращаемое t у плоскости
    if (closest_plane)
    {
        init_color(&object_params->color, closest_plane->color.r, closest_plane->color.g, closest_plane->color.b);
        init_vector(&object_params->norm, closest_plane->direction.x, closest_plane->direction.y, closest_plane->direction.z);
        vector_normalize(&(object_params->norm));
        return (closest_t);
    }
    return (0);
}