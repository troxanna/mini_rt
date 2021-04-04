#include "../../../includes/minirt.h"

// static int     intersect_plane(t_vector *ray_orig, t_vector *ray_dir, float *t, t_plane *plane)
// {
//     float       denom;
//     float y;
//     t_vector    LP;
//     vector_normalize(&(plane->direction));
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
    vector_normalize(&n);
    vector_normalize(ray_dir);
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

float           iterate_object_plane(t_plane *plane, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    t_plane    *ptr;
    float       tmp;
    //t_vector    ray_dir_tmp;

    tmp = 0;
    ptr = plane;
    while (ptr)
    {
        if ((intersect_plane(ray_orig, ray_dir, t, ptr)))
        {
            if ((t[0] > t[1] && t[0] < t[2] && t[0] < tmp) || (tmp == 0 && t[0] >= t[1] && t[0] < t[2]))
            {
                tmp = t[0];
                init_vector(&(object_params->norm), plane->direction.x, plane->direction.y, plane->direction.z);
                //vector_subtraction(&(object_params->norm), &(object_params->intersect_point), &(ptr->center));
                init_color(&(object_params->color), ptr->color.r, ptr->color.g, ptr->color.b);
            }
        }
        ptr = ptr->next;
    }
    t[0] = tmp;
    //printf ("%f\n", tmp);
    return (tmp);
}