#include "../../../includes/minirt.h"

static int       square_intersect(t_vector *ray_orig, t_vector *ray_dir, float *t, t_square *square, t_object_params *object_params)
{
    float       ab[2];
    float       t1;
    float       t2;
    t_vector    d[2];
    t_vector    ray_dir_tmp;

    init_vector(&(object_params->norm), square->direction.x, square->direction.y, square->direction.z);
    vector_normalize(&(object_params->norm));
    vector_subtraction(&d[0], ray_orig, &(square->center_square));
    ab[0] = vector_dot_products(&d[0], &(object_params->norm));
    ab[1] = vector_dot_products(ray_dir, &(object_params->norm));
    if (ab[1] == 0 || (ab[0] < 0 && ab[1] < 0) || (ab[0] > 0 && ab[1] > 0))
        return (0);
    t1 = -(ab[0] / ab[1]);
    init_vector(&ray_dir_tmp, ray_dir->x, ray_dir->y, ray_dir->z);
    scalars_mult_vectors(t1, &ray_dir_tmp);
    vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
    vector_subtraction(&d[1], &(object_params->intersect_point), &(square->center_square));
    t2 = square->side / 2;
    if (fabs(d[1].x) > t2 || fabs(d[1].y) > t2 || fabs(d[1].z) > t2)
        return (0);
    if (t1 > 0)
    {
        t[0] = t1;
        return (1);
    }
    return (0);
}

float           iterate_object_square(t_square *square, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    t_square    *ptr;
    float       tmp;
    //t_vector    ray_dir_tmp;


    tmp = 0;
    ptr = square;
    while (ptr)
    {
        if ((square_intersect(ray_orig, ray_dir, t, ptr, object_params)))
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