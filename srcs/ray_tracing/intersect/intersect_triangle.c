#include "../../../includes/minirt.h"

static int                 check_point_triangle_inside(t_triangle *triangle, t_vector *intersect_point, t_vector *norm)
{
    t_vector        edge[3];
    t_vector        C[3];
    t_vector        C_result;

    vector_subtraction(&edge[0], &(triangle->second_point), &(triangle->first_point));
    vector_subtraction(&edge[1], &(triangle->third_point), &(triangle->second_point));
    vector_subtraction(&edge[2], &(triangle->first_point), &(triangle->third_point));
    vector_subtraction(&C[0], intersect_point, &(triangle->first_point));
    vector_subtraction(&C[1], intersect_point, &(triangle->second_point));
    vector_subtraction(&C[2], intersect_point, &(triangle->third_point));
    vector_cross_products(&C_result, &edge[0], &C[0]);
    if (vector_dot_products(norm, &C_result) < 0)
        return (0);
    vector_cross_products(&C_result, &edge[1], &C[1]);
    if (vector_dot_products(norm, &C_result) < 0)
        return (0);
    vector_cross_products(&C_result, &edge[2], &C[2]);
    if (vector_dot_products(norm, &C_result) < 0)
        return (0);
    return (1);
}

static void        get_norm_triangle(t_triangle *triangle, t_vector *norm)
{   
    t_vector A;
    t_vector B;

//учитывать систему координат (если будет рисоваться зеркально, то надо повернуть нормаль и камеру по оси z)
    vector_subtraction(&A, &(triangle->second_point), &(triangle->first_point));
    vector_subtraction(&B, &(triangle->third_point), &(triangle->first_point));
    vector_cross_products(norm, &A, &B);
    vector_normalize(norm);
}

static int     triangle_intersect(t_triangle *triangle, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    float D;
    float ND;
    t_vector ray_dir_tmp;

    get_norm_triangle(triangle, &(object_params->norm)); 
    //vector_normalize(&(object_params->norm));
    // printf("%f, ", object_params->norm.x);
    // printf("%f, ", object_params->norm.y);
    // printf("%f\n", object_params->norm.z);
    // printf("%f, ", ray_dir->x);
    // printf("%f, ", ray_dir->y);
    // printf("%f\n", ray_dir->z);
    ND = vector_dot_products(&(object_params->norm), ray_dir);
   // printf("%f, ", ND);
    if (ND < 0.000001 && ND > -0.000001)
        return (0);
    D = vector_dot_products(&(object_params->norm), &(triangle->first_point));
    t[0] = (vector_dot_products(&(object_params->norm), ray_orig) + D) / ND;
    if (t[0] < 0)
    {
        return (0);
    }
    init_vector(&ray_dir_tmp, ray_dir->x, ray_dir->y, ray_dir->z);
    scalars_mult_vectors(t[0], &ray_dir_tmp);
    vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
    if (check_point_triangle_inside(triangle, &(object_params->intersect_point), &(object_params->norm)))
        return (1);
    else
        return (0);
}

float           iterate_object_triangle(t_triangle *triangle, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    t_triangle    *ptr;
    float       tmp;
    //t_vector    ray_dir_tmp;


    tmp = 0;
    ptr = triangle;
    while (ptr)
    {
        if ((triangle_intersect(ptr, object_params, ray_dir, ray_orig, t)))
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