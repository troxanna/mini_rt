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
    //vector_normalize(ray_dir);
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

float           iterate_object_square(t_square *square, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig)
{
    t_square    *ptr;
    float   range_t[3];
    float       closest_t;
    t_square    *closest_square;

    range_t[0] = 0;
    range_t[1] = 0.000001;
    range_t[2] = 65536;
    closest_square = NULL;
    closest_t = 65536;
    ptr = square;
    while (ptr)
    {
        if ((square_intersect(ray_orig, ray_dir, &range_t[0], ptr, object_params)))
        {
            if (range_t[0] >= range_t[1] && range_t[0] < range_t[2] && range_t[0] < closest_t)
            {
                closest_t = range_t[0];
                closest_square = ptr;
            }
        }
        ptr = ptr->next;
    }
    if (closest_square)
    {
        init_color(&object_params->color, closest_square->color.r, closest_square->color.g, closest_square->color.b);
        return (closest_t);
    }
    return (0);
}