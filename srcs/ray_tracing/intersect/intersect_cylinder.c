#include "../../../includes/minirt.h"

static int     cylinder_intersect(t_vector *ray_orig, t_vector *ray_dir, float *t, t_cylinder *cylinder, t_object_params *object_params)
{

    t_vector    X;
    t_vector    tmp[4];
    float       coefficient[3];
    float       m;
    
    vector_normalize(&(cylinder->direction));
    vector_subtraction(&X, ray_orig, &(cylinder->point_cylinder));
    coefficient[0] = vector_dot_products(ray_dir, ray_dir) - pow(vector_dot_products(ray_dir, &(cylinder->direction)), 2);
    coefficient[1] = 2 * ((vector_dot_products(ray_dir, &X) - vector_dot_products(ray_dir, &(cylinder->direction)) * vector_dot_products(&X, &(cylinder->direction))));
    coefficient[2] = vector_dot_products(&X, &X) - pow(vector_dot_products(&X, &(cylinder->direction)), 2) - pow(cylinder->diameter / 2, 2);
    if ((t[0] = solve_quadratic(coefficient[0], coefficient[1], coefficient[2])) < 0)
        return (0);
    else
    {
        init_vector(&tmp[2], cylinder->direction.x, cylinder->direction.y, cylinder->direction.z);
        scalars_mult_vectors(t[0], &tmp[2]);
        m = vector_dot_products(ray_dir, &tmp[2]) + vector_dot_products(&X, &(cylinder->direction));
        if (m >= 0 && m <= cylinder->height)
        {
            init_vector(&tmp[1], ray_dir->x * t[0], ray_dir->y * t[0], ray_dir->z * t[0]);
            vector_addition(&(object_params->intersect_point), ray_orig, &tmp[1]);
            init_vector(&tmp[0], cylinder->direction.x * m, cylinder->direction.y * m, cylinder->direction.z * m);
            //P - C = D*t + X
            vector_addition(&tmp[3], &tmp[1], &X);
            vector_subtraction(&(object_params->norm), &tmp[2], &tmp[3]);
            //norm = nrm( P-C-V*m )
            return (1);
        }
        else
            return (0);
    }
}

float           iterate_object_cylinder(t_cylinder *cylinder, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    t_cylinder    *ptr;
    float       tmp;
    //t_vector    ray_dir_tmp;

    tmp = 0;
    ptr = cylinder;
    while (ptr)
    {
        if ((cylinder_intersect(ray_orig, ray_dir, t, cylinder, object_params)))
        {
            if ((t[0] >= t[1] && t[0] < t[2] && t[0] < tmp) || (tmp == 0 && t[0] >= t[1] && t[0] < t[2]))
            {
                tmp = t[0];
                //ray_dir_tmp = *ray_dir;
                //scalars_mult_vectors(t[0], &ray_dir_tmp);
                //vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
                //vector_subtraction(&(object_params->norm), &(object_params->intersect_point), &(ptr->center));
                init_color(&(object_params->color), ptr->color.r, ptr->color.g, ptr->color.b);
            }
        }
        ptr = ptr->next;
    }
    t[0] = tmp;
    return (tmp);
}