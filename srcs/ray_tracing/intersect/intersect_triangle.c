#include "../../../includes/minirt.h"

// static void      reverse_normal(t_vector *norm)
// {
//     // norm->x = norm->x * (-1);
//     // norm->y = norm->y * (-1);
//     norm->z = norm->z * (-1);
// }

// static int                 check_point_triangle_inside(t_triangle *triangle, t_vector *intersect_point, t_vector *norm)
// {
//     t_vector        edge[3];
//     t_vector        C[3];
//     t_vector        C_result;

//     vector_subtraction(&edge[0], &(triangle->second_point), &(triangle->first_point));
//     vector_subtraction(&edge[1], &(triangle->third_point), &(triangle->second_point));
//     vector_subtraction(&edge[2], &(triangle->first_point), &(triangle->third_point));
//     vector_subtraction(&C[0], intersect_point, &(triangle->first_point));
//     vector_subtraction(&C[1], intersect_point, &(triangle->second_point));
//     vector_subtraction(&C[2], intersect_point, &(triangle->third_point));
//     vector_cross_products(&C_result, &edge[0], &C[0]);
//     if (vector_dot_products(norm, &C_result) < 0)
//         return (0);
//     vector_cross_products(&C_result, &edge[1], &C[1]);
//     if (vector_dot_products(norm, &C_result) < 0)
//         return (0);
//     vector_cross_products(&C_result, &edge[2], &C[2]);
//     if (vector_dot_products(norm, &C_result) < 0)
//         return (0);
//     return (1);
// }

// static void        get_norm_triangle(t_triangle *triangle, t_vector *norm)
// {   
//     t_vector A;
//     t_vector B;

// //если невозможно построить треугольник - обрабатывать это и выдавать ошибку
//     vector_subtraction(&A, &(triangle->second_point), &(triangle->first_point));
//     vector_subtraction(&B, &(triangle->third_point), &(triangle->first_point));
//     vector_cross_products(norm, &A, &B);
//     //разобраться с нормалью по статье в скрэтчпиксель
//     //vector_normalize(norm);
//     //reverse_normal(norm);
// }

// static int     triangle_intersect(t_triangle *triangle, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
// {
//     float D;
//     float ND;
//     t_vector ray_dir_tmp;

//     vector_normalize(ray_dir);
//     get_norm_triangle(triangle, &(object_params->norm)); 
//     //vector_normalize(&(object_params->norm));
//     // printf("%f, ", object_params->norm.x);
//     // printf("%f, ", object_params->norm.y);
//     // printf("%f\n", object_params->norm.z);
//     // printf("%f, ", ray_dir->x);
//     // printf("%f, ", ray_dir->y);
//     // printf("%f\n", ray_dir->z);
//     ND = vector_dot_products(&(object_params->norm), ray_dir);
//    // printf("%f, ", ND);
//     if (fabs(ND) < 0.000001)
//         return (0);
//     D = vector_dot_products(&(object_params->norm), &(triangle->first_point));
//     t[0] = (vector_dot_products(&(object_params->norm), ray_orig) + D) / ND;
//     if (t[0] < 0)
//     {
//         return (0);
//     }
//     init_vector(&ray_dir_tmp, ray_dir->x, ray_dir->y, ray_dir->z);
//     scalars_mult_vectors(t[0], &ray_dir_tmp);
//     vector_addition(&(object_params->intersect_point), ray_orig, &ray_dir_tmp);
//     if (check_point_triangle_inside(triangle, &(object_params->intersect_point), &(object_params->norm)))
//         return (1);
//     else
//         return (0);
// }

static int     triangle_intersect(t_triangle *triangle, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig, float *t)
{
    float det;
    float inv_det;
    float ND;
    float u;
    t_vector q_vec;
    t_vector t_vec;
    t_vector A;
    t_vector B;
    float v;

    //vector_normalize(ray_dir);
    vector_subtraction(&A, &(triangle->second_point), &(triangle->first_point));
    vector_subtraction(&B, &(triangle->third_point), &(triangle->first_point));
    //vector_normalize(&A);
    //vector_normalize(&B);
    vector_cross_products(&(object_params->norm), ray_dir, &B);
    //vector_normalize(&(object_params->norm));
    det = vector_dot_products(&A, &(object_params->norm));
    if (det < 0.00001 && det > -0.00001)
        return 0;
    inv_det = 1 / det;
    vector_subtraction(&t_vec, ray_orig, &(triangle->first_point));
    //vector_normalize(&t_vec);
    u = vector_dot_products(&t_vec, &(object_params->norm)) * inv_det;
    if (u < 0 || u > 1)
        return 0;
    vector_cross_products(&q_vec, &t_vec, &A);
    //vector_normalize(&q_vec);
    v = vector_dot_products(ray_dir, &q_vec) * inv_det;
    if (v < 0 || (u + v) > 1)
        return 0;
    t[0] = vector_dot_products(&B, &q_vec) * inv_det;
    //vector_normalize(&(object_params->norm));
    if (t[0] > 0.001)
        return (1);
    else 
        return (0);
}

float           iterate_object_triangle(t_triangle *triangle, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig)
{
    t_triangle    *ptr;
    float   range_t[3];
    float       closest_t;
    t_triangle    *closest_triangle;

    range_t[0] = 0;
    range_t[1] = 0.1;
    range_t[2] = 65536;
    closest_triangle = NULL;
    closest_t = 65536;
    ptr = triangle;
    while (ptr)
    {
        if ((triangle_intersect(ptr, object_params, ray_dir, ray_orig, range_t)))
        {
            if (range_t[0] >= range_t[1] && range_t[0] < range_t[2] && range_t[0] < closest_t)
            {
                closest_t = range_t[0];
                closest_triangle = ptr;
            }
        }
        ptr = ptr->next;
    }
    if (closest_triangle)
    {
        init_color(&object_params->color, closest_triangle->color.r, closest_triangle->color.g, closest_triangle->color.b);
        return (closest_t);
    }
    return (0);
}