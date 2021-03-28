#include "../../../includes/minirt.h"

int       check_point_triangle_inside(t_triangle *triangle, t_vector *intersect_point, t_vector *norm)
{
    t_vector *edge_1;
    t_vector *edge_2;
    t_vector *edge_3;

    t_vector *C_1;
    t_vector *C_2;
    t_vector *C_3;

    t_vector *C;

    edge_1 = vector_subtraction(triangle->second_point, triangle->first_point);
    edge_2 = vector_subtraction(triangle->third_point, triangle->second_point);
    edge_3 = vector_subtraction(triangle->first_point, triangle->third_point);
    C_1 = vector_subtraction(intersect_point, triangle->first_point);
    C_2 = vector_subtraction(intersect_point, triangle->second_point);
    C_3 = vector_subtraction(intersect_point, triangle->third_point);
    C = vector_cross_products(C, edge_1, C_1);
    free_calculate_triangle(edge_1, C_1);
    if (vector_dot_products(norm, C) < 0)
        return (0);
    //free(C);
    C = vector_cross_products(C, edge_2, C_2);
    free_calculate_triangle(edge_2, C_2);
    if (vector_dot_products(norm, C) < 0)
        return (0);
    //free(C);
    C = vector_cross_products(C, edge_3, C_3);
    free_calculate_triangle(edge_3, C_3);
    if (vector_dot_products(norm, C) < 0)
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

int     intersect_triangle(t_triangle *triangle, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    float D;
    float ND;
    t_vector ray_dir_tmp;

    get_norm_triangle(triangle, &(object_params->norm)); 
    vector_normalize(&(object_params->norm));
    ND = vector_dot_products(&(object_params->norm), ray_dir);
    if (ND < 0.000001 && ND > -0.000001)
    {
        *t = -1;
        return (0);
    }
    D = vector_dot_products(&(object_params->norm), &(triangle->first_point));
    *t = (vector_dot_products(&(object_params->norm), ray_orig) + D) / ND;
    if (*t < 0)
    {   
        return (0);
    }
    init_vector(&ray_dir_tmp, ray_dir->x, ray_dir->y, ray_dir->z);
    scalars_mult_vectors(*t, &ray_dir_tmp);
    vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
    if (check_point_triangle_inside(triangle, &(object_params->intersect_point), &(object_params->norm)))
        return (1);
    else
    {
        *t = -1;
        return (0);
    }
}
