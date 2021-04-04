#include "../../../includes/minirt.h"

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

float           iterate_object_sphere(t_sphere *sphere, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    t_sphere    *ptr;
    float       tmp;
    t_vector    ray_dir_tmp;

    tmp = 0;
    ptr = sphere;
    while (ptr)
    {
        if ((sphere_intersect(ray_orig, ray_dir, t, ptr)))
        {
            if ((t[0] >= t[1] && t[0] < t[2] && t[0] < tmp) || (tmp == 0 && t[0] >= t[1] && t[0] < t[2]))
            {
                tmp = t[0];
                ray_dir_tmp = *ray_dir;
                scalars_mult_vectors(t[0], &ray_dir_tmp);
                vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
                vector_subtraction(&(object_params->norm), &(object_params->intersect_point), &(ptr->center));
                init_color(&(object_params->color), ptr->color.r, ptr->color.g, ptr->color.b);
            }
        }
        ptr = ptr->next;
    }
    t[0] = tmp;
    return (tmp);
}