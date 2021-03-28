#include "../../includes/minirt.h"

void   init_vector(t_vector *result, float x, float y, float z)
{
    result->x = x;
    result->y = y;
    result->z = z;
}

t_vector    *new_vector(float x, float y, float z)
{
    t_vector    *result;

    if (!(result = malloc(sizeof(t_vector))))
        ft_error(1);
    result->x = x;
    result->y = y;
    result->z = z;

    return (result);
}

void        vector_addition(t_vector *result, t_vector *v1, t_vector *v2)
{
    result->x = v1->x + v2->x;
    result->y = v1->y + v2->y;
    result->z = v1->z + v2->z;
}

void        vector_subtraction(t_vector *result, t_vector *v1, t_vector *v2)
{
    result->x = v1->x - v2->x;
    result->y = v1->y - v2->y;
    result->z = v1->z - v2->z;
}

float       vector_length(t_vector *v)
{
    float   len;

    if (!(len = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z))))
        exit(EXIT_FAILURE);
    return (len);
}

void        vector_normalize(t_vector *v)
{
    float len;

    len = vector_length(v);
    v->x = v->x / len;
    v->y = v->y / len;
    v->z = v->z / len;
}

void        scalars_mult_vectors(float scalar, t_vector *vector)
{
    vector->x = vector->x * scalar;
    vector->y = vector->y * scalar;
    vector->z = vector->z * scalar;
}

float       vector_dot_products(t_vector *v1, t_vector *v2)
{
    float result;
    result = (v1->x * v2->x) + (v1->y * v2->y) + (v1->z * v2->z);
    return (result);
}

void        vector_cross_products(t_vector *result, t_vector *v1, t_vector *v2)
{
    result->x = (v1->y * v2->z) - (v1->z * v2->y);
    result->y = (v1->z * v2->x) - (v1->x * v2->z);
    result->z = (v1->x * v2->y) - (v1->y * v2->x);
}


t_vector       *matrix_to_world(t_vector *ray_dir, t_vector *camera_dir)
{
    t_vector    tmp_vector;
    t_vector    vector_x;
    t_vector    vector_y;
    t_vector    *result;

    vector_normalize(camera_dir);
    init_vector(&tmp_vector, 0, 1, 0);
    result = new_vector(0, 0, 0);
    vector_cross_products(&vector_x, &tmp_vector, camera_dir);
    vector_cross_products(&vector_y, camera_dir, &vector_x);
    result->x = ray_dir->x * vector_x.x + ray_dir->y * vector_x.y + ray_dir->z * vector_x.z;
    result->y = ray_dir->x * vector_y.x + ray_dir->y * vector_y.y + ray_dir->z * vector_y.z;
    result->z = ray_dir->x * camera_dir->x + ray_dir->y * camera_dir->y + ray_dir->z * camera_dir->z;
    return (result);
}



