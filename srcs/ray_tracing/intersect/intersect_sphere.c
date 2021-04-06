#include "../../../includes/minirt.h"

static void     get_normal_sphere(t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float closest_t, t_sphere *sphere)
{
    t_vector    ray_dir_tmp;

    ray_dir_tmp = *ray_dir;
    scalars_mult_vectors(closest_t, &ray_dir_tmp);
    vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
    vector_subtraction(&(object_params->norm), &(object_params->intersect_point), &(sphere->center));
    init_color(&(object_params->color), sphere->color.r, sphere->color.g, sphere->color.b);
}

static int     sphere_intersect(t_vector *ray_orig, t_vector *ray_dir, float *t, t_sphere *sphere)
{

    t_vector L;
    float a;
    float b;
    float c;
    
    vector_subtraction(&L, ray_orig, &(sphere->center));
    a = vector_dot_products(ray_dir, ray_dir);
    b = vector_dot_products(&L, ray_dir) * 2;
    c = vector_dot_products(&L, &L) - pow(sphere->radius, 2);
    if ((t[0] = solve_quadratic(a, b, c)) < 0)
    {
        //printf("%f\n", t);
        return (0);
    }
    else
    {
        //printf("%f\n", t);
        return (1);
    }
}

float           iterate_object_sphere(t_sphere *sphere, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig)
{
    t_sphere    *ptr;
    t_sphere    *closest_sphere;
    float       range_t[3];
    float       closest_t;
    //t_vector    ray_dir_tmp;

    range_t[0] = 0;
    range_t[1] = 1;
    range_t[2] = 65536;
    closest_sphere = NULL;
    closest_t = 65536;
    ptr = sphere;
    while (ptr)
    {
        if ((sphere_intersect(ray_orig, ray_dir, range_t, ptr)))
        {
            if (range_t[0] >= range_t[1] && range_t[0] < range_t[2] && range_t[0] < closest_t)
            {
                closest_t = range_t[0];
                closest_sphere = ptr;
            }
            // if ((t[0] >= t[1] && t[0] < t[2] && t[0] < tmp) || (tmp == 0 && t[0] >= t[1] && t[0] < t[2]))
            // {
            //     tmp = t[0];
            //     ray_dir_tmp = *ray_dir;
            //     scalars_mult_vectors(t[0], &ray_dir_tmp);
            //     vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
            //     vector_subtraction(&(object_params->norm), &(object_params->intersect_point), &(ptr->center));
            //     init_color(&(object_params->color), ptr->color.r, ptr->color.g, ptr->color.b);
            // }
        }
        ptr = ptr->next;
    }
    //t[0] = tmp;
    if (closest_sphere)
    {
        get_normal_sphere(object_params, ray_dir, ray_orig, closest_t, closest_sphere);
        return (closest_t);
    }
    return (0);
}