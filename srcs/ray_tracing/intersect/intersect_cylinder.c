#include "../../../includes/minirt.h"
#include "stdio.h"


// static int     intersect_cylinder(t_vector *ray_orig, t_vector *ray_dir, float *t, t_cylinder *cylinder, t_object_params *object_params)
// {

//     t_vector    X;
//     t_vector    ray_dir_tmp;
//     t_vector    tmp[6];
//     float       coefficient[3];
//     float       m;
//     float       D;
//     float       dist1;
//     float       dist2;
//     float           tmp_t;
//     m = 0;
    
//     //vector_normalize(ray_dir);
//     vector_normalize(&(cylinder->direction));
//     vector_subtraction(&X, ray_orig, &(cylinder->point_cylinder));
//     coefficient[0] = vector_dot_products(ray_dir, ray_dir) - pow(vector_dot_products(ray_dir, &(cylinder->direction)), 2);
//     coefficient[1] = 2 * ((vector_dot_products(ray_dir, &X) - vector_dot_products(ray_dir, &(cylinder->direction)) * vector_dot_products(&X, &(cylinder->direction))));
//     coefficient[2] = vector_dot_products(&X, &X) - pow(vector_dot_products(&X, &(cylinder->direction)), 2) - pow(cylinder->diameter / 2, 2);
//     // D = pow(coefficient[1], 2) - (4 * coefficient[0] * coefficient[2]);
//     // if (D < 0)
//     //     return (0);
//     // dist1 = ((coefficient[1] * (-1)) + sqrt(D)) / 2 * coefficient[0];
//     // dist2 = ((coefficient[1] * (-1)) - sqrt(D)) / 2 * coefficient[0];
//     // if (dist1 > 0 && dist1 < dist2)
//     //     t[0] = dist1;
//     // else if (dist2 > 0 && dist2 < dist1)
//     //     t[0] = dist2;
//     if ((solve_quadratic(coefficient[0], coefficient[1], coefficient[2], t)) < 0)
//         return (0);

//     if (intersect_cylinder_main(ray_orig, ray_dir, t, cylinder, object_params))
//     {

//     }
//     else
//     {
//         if ((tmp_t = check_m_cylinder(t, cylinder, ray_dir, &X, &m) > 0))
//         {
//             init_vector(&tmp[1], ray_dir->x * tmp_t, ray_dir->y * tmp_t, ray_dir->z * tmp_t);
//             vector_addition(&(object_params->intersect_point), ray_orig, &tmp[1]);
//             init_vector(&tmp[0], cylinder->direction.x * m, cylinder->direction.y * m, cylinder->direction.z * m);
//             //P - C = D*t + X == tmp[3]
//             vector_addition(&tmp[3], &tmp[1], &X);
//             // V*m == tmp[0]
//             vector_subtraction(&(object_params->norm), &tmp[3], &tmp[0]);
//             vector_normalize(&(object_params->norm));
//             // init_vector(&tmp[4], object_params->norm.x * 0.01, object_params->norm.y * 0.01, object_params->norm.z * 0.01);
//             // vector_addition(&(object_params->intersect_point), &(object_params->intersect_point), &tmp[4]);
//             return (1);
//         }
//         else 
//         // else
//         // {
//         //     init_vector(&tmp[2], cylinder->direction.x, cylinder->direction.y, cylinder->direction.z);
//         //     scalars_mult_vectors(t[1], &tmp[2]);
//         //     m = vector_dot_products(ray_dir, &tmp[2]) + vector_dot_products(&X, &(cylinder->direction));
//         //     if (m >= 0 && m <= cylinder->height)
//         //     {
//         //         init_vector(&tmp[1], ray_dir->x * t[0], ray_dir->y * t[0], ray_dir->z * t[0]);
//         //         vector_addition(&(object_params->intersect_point), ray_orig, &tmp[1]);
//         //         init_vector(&tmp[0], cylinder->direction.x * m, cylinder->direction.y * m, cylinder->direction.z * m);
//         //         //P - C = D*t + X == tmp[3]
//         //         vector_addition(&tmp[3], &tmp[1], &X);
//         //         // V*m == tmp[0]
//         //         vector_subtraction(&(object_params->norm), &tmp[3], &tmp[0]);
//         //         vector_normalize(&(object_params->norm));
//         //         init_vector(&tmp[4], object_params->norm.x * 0.001, object_params->norm.y * 0.001, object_params->norm.z * 0.001);
//         //         vector_addition(&(object_params->intersect_point), &(object_params->intersect_point), &tmp[4]);
//         //         return (1);
//         //     }
//         //     else
//         //         return (0);
//         // }
//         return (0);
//     }
//     return (0);
// }












static void             get_normal_cylinder(t_vector *X, float t, float m, t_object_params *object_params, t_vector *ray_dir, t_vector *direction, t_vector *ray_orig)
{   
    t_vector tmp[4];

    init_vector(&tmp[0], ray_dir->x * t, ray_dir->y * t, ray_dir->z * t);
    // vector_addition(&(object_params->intersect_point), ray_orig, &tmp[4]);
    //P - C = D*t + X == tmp[3]
    vector_addition(&tmp[2], &tmp[0], X);
    // V*m == tmp[1]
    init_vector(&tmp[1], direction->x * m, direction->y * m, direction->z * m);
    vector_subtraction(&(object_params->norm), &tmp[2], &tmp[1]);
    vector_normalize(&(object_params->norm));
    // init_vector(&tmp[3], object_params->norm.x * 0.01, object_params->norm.y * 0.01, object_params->norm.z * 0.01);
    // vector_addition(&(object_params->intersect_point), &(object_params->intersect_point), &tmp[3]);
}

static int             intersect_cylinder(t_vector *ray_orig, t_vector *ray_dir, float *t, t_cylinder *cylinder, t_object_params *object_params)
{
    float	vec[3];
	double	m;
	double	closet_t;
    float   coef[3];
    t_vector    X;
	//t_eq	eq;

	closet_t = 65536;
    //vector_normalize(ray_dir);
    vector_normalize(&(cylinder->direction));
    vector_subtraction(&X, ray_orig, &(cylinder->point_cylinder));
	//v_substr(o, obj->xyz, oc);
	coef[0] = vector_dot_products(ray_dir, ray_dir) - pow(vector_dot_products(ray_dir, &(cylinder->direction)), 2);
	coef[1] = 2.0 * (vector_dot_products(ray_dir, &X) - vector_dot_products(ray_dir, &(cylinder->direction)) * vector_dot_products(&X, &(cylinder->direction)));
	coef[2] = vector_dot_products(&X, &X) - vector_dot_products(&X, &(cylinder->direction)) *
		vector_dot_products(&X, &(cylinder->direction)) - pow(cylinder->diameter / 2, 2);
	closet_t = solve_quadratic(coef[0], coef[1], coef[2], t);
	if (!(closet_t < 65536))
		return (0);
	m = vector_dot_products(ray_dir, &(cylinder->direction)) * closet_t + vector_dot_products(&X, &(cylinder->direction));
	if (m >= 0.0 && m <= cylinder->height)
	{
        get_normal_cylinder(&X, closet_t, m, object_params, ray_dir, &(cylinder->direction), ray_orig);
        t[0] = closet_t;
        return (1);
    }
	if (closet_t == t[0])
		closet_t = t[1];
	else if (closet_t == t[1])
		closet_t = t[0];
	m = vector_dot_products(ray_dir, &(cylinder->direction)) * closet_t + vector_dot_products(&X, &(cylinder->direction));
	if (m >= 0.0 && m <= cylinder->height)
	{
        get_normal_cylinder(&X, closet_t, m, object_params, ray_dir, &(cylinder->direction), ray_orig);
        t[0] = closet_t;
        return (1);
    }
	return (0);
}





// static int     intersect_cylinder(t_vector *ray_orig, t_vector *ray_dir, float *t, t_cylinder *cylinder, t_object_params *object_params)
// {

//     t_vector    X;
//     t_vector    tmp[4];
//     float       coefficient[3];
//     float       m;
    
//     vector_normalize(&(cylinder->direction));
//     vector_subtraction(&X, ray_orig, &(cylinder->point_cylinder));
//     coefficient[0] = vector_dot_products(ray_dir, ray_dir) - pow(vector_dot_products(ray_dir, &(cylinder->direction)), 2);
//     coefficient[1] = 2 * ((vector_dot_products(ray_dir, &X) - vector_dot_products(ray_dir, &(cylinder->direction)) * vector_dot_products(&X, &(cylinder->direction))));
//     coefficient[2] = vector_dot_products(&X, &X) - pow(vector_dot_products(&X, &(cylinder->direction)), 2) - pow(cylinder->diameter / 2, 2);
//     if ((t[0] = solve_quadratic(coefficient[0], coefficient[1], coefficient[2], t)) < 0)
//         return (0);
//     else
//     {
//         init_vector(&tmp[2], cylinder->direction.x, cylinder->direction.y, cylinder->direction.z);
//         scalars_mult_vectors(t[0], &tmp[2]);
//         m = vector_dot_products(ray_dir, &tmp[2]) + vector_dot_products(&X, &(cylinder->direction));
//         if (m >= 0 && m <= cylinder->height)
//         {
//             init_vector(&tmp[1], ray_dir->x * t[0], ray_dir->y * t[0], ray_dir->z * t[0]);
//             vector_addition(&(object_params->intersect_point), ray_orig, &tmp[1]);
//             init_vector(&tmp[0], cylinder->direction.x * m, cylinder->direction.y * m, cylinder->direction.z * m);
//             //P - C = D*t + X
//             vector_addition(&tmp[3], &tmp[1], &X);
//             vector_subtraction(&(object_params->norm), &tmp[2], &tmp[3]);
//             //norm = nrm( P-C-V*m )
//             return (1);
//         }
//         else
//             return (0);
//     }
// }


float           iterate_object_cylinder(t_cylinder *cylinder, t_object_params *object_params, t_vector *ray_dir, t_vector *ray_orig)
{
    t_cylinder    *ptr;
    float   range_t[4];
    float       closest_t;
    t_cylinder    *closest_cylinder;

    range_t[0] = 0;
    range_t[2] = 0.00000001;
    range_t[3] = 65536;
    closest_cylinder = NULL;
    closest_t = 65536;
    ptr = cylinder;
    while (ptr)
    {
        if ((intersect_cylinder(ray_orig, ray_dir, range_t, ptr, object_params)))
        {
            if (range_t[0] >= range_t[2] && range_t[0] < range_t[3] && range_t[0] < closest_t)
            {
                closest_t = range_t[0];
                closest_cylinder = ptr;
            }
        }
        ptr = ptr->next;
    }
    //проверить возвращаемое t у цилиндра
    if (closest_cylinder)
    {
        init_color(&object_params->color, closest_cylinder->color.r, closest_cylinder->color.g, closest_cylinder->color.b);
        vector_normalize(&(object_params->norm));
        return (closest_t);
    }
    return (0);
}