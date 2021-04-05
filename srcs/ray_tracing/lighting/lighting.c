#include "../../../includes/minirt.h"

// static int     angle_between_norm_and_light(t_vector *norm, t_vector *L)
// {
//   float   len_NL;
//   float   cos;
//   float   angle;

//   len_NL = vector_length(norm) * vector_length(L);
//   cos = vector_length(L) / len_NL;
//   angle = acos(cos) * 180 / M_PI;
//   if (angle > 90)
//     return (1);
//   else
//     return (0);
// }

static int     shadow_check(t_object_figure *obj_figure, t_vector *L, t_vector *intersect_point)
{
  float   range_t[3];
  t_object_params object_params_tmp;

  range_t[0] = 0;
  range_t[1] = 0.01;
  range_t[2] = 0.9;
  // t_vector    tmp_inter;
  // init_vector(&tmp_inter, )
  //range_t[2] = 0.9999;
  //printf("%p\n", &(obj_figure->triangle));

  if (obj_figure->sphere && iterate_object_sphere(obj_figure->sphere, &object_params_tmp, L, intersect_point, range_t))
  {
    if (range_t[0] > range_t[1] && range_t[0] < range_t[2])
        printf("%f\n", range_t[0]);
    return (1);
  }
  // if (obj_figure->triangle && iterate_object_triangle(obj_figure->triangle, &object_params_tmp, L, intersect_point, range_t))
  //     return (1);
  // if (obj_figure->plane && iterate_object_plane(obj_figure->plane, &object_params_tmp, L, intersect_point, range_t));
  //     return (1);
  return (0);
}

static void    add_intensity_point_light(float *intensity, t_point_light *light, float NL)
{
    intensity[0] = intensity[0] + light->brightness * light->color.r / 255 * NL;
    intensity[1] = intensity[1] + light->brightness * light->color.g / 255 * NL;
    intensity[2] = intensity[2] + light->brightness * light->color.b / 255 * NL;
}

//отдельная функция для суммы цвета источников света
static void         get_color_sum_point_lights(t_object_figure *obj_figure,
                                            t_point_light *point_lights, t_object_params *obj_params, float *intensity)
{
  t_point_light     *ptr;
  t_vector          L;
  float             NL;
  float             t;
  int               tmp;

  t = 0;
  tmp = 0;
  ptr = point_lights;

  while (ptr)
  {
    vector_subtraction(&L, &(ptr->point_light), &(obj_params->intersect_point));
    vector_normalize(&L);
    NL = vector_dot_products(&(obj_params->norm), &L);
    if (NL < 0 && !obj_params->flag)
        tmp = 1;
    // else if (NL < 0 && obj_params->flag)
    // {
    //     //obj_params->norm.z = obj_params->norm.z * (-1);
    //     scalars_mult_vectors(-1, &(obj_params->norm));
    //     NL = vector_dot_products(&(obj_params->norm), &L);
    // }
    tmp = shadow_check(obj_figure, &L, &(obj_params->intersect_point));
    if (tmp == 1)
      printf("%d\n", tmp);
    if (tmp == 0)
      add_intensity_point_light(intensity, ptr, NL);
    //printf("%d\n", tmp);
    ptr = ptr->next;
  }
}

static int      get_final_color(t_rgb *object_color, float intensity_lights[3])
{
  t_rgb         final_color;

  init_color(&final_color, object_color->r * intensity_lights[0], object_color->g * intensity_lights[1], object_color->b * intensity_lights[2]);
  if (final_color.r > 255)
    final_color.r = 255;
  if (final_color.g > 255)
    final_color.g = 255;
  if (final_color.b > 255)
    final_color.b = 255;
  return (create_trgb(0, final_color.r, final_color.g, final_color.b));
}

int   get_light_point(t_object_lights *lights, t_object_params *obj_params, t_object_figure *obj_figure)
{
  float intensity_sum_lights[3];
  float intensity_ambient_light[3];
  float intensity_point_lights[3];
  int color;
  // printf("%d\n", obj_params->color.r);
  // printf("%d\n", obj_params->color.g);
  // printf("%d\n", obj_params->color.b);
  vector_normalize(&(obj_params->norm));
  // printf("%f\n", obj_params->norm.x);
  // printf("%f\n", obj_params->norm.y);
  // printf("%f\n", obj_params->norm.z);
  
  intensity_point_lights[0] = 0;
  intensity_point_lights[1] = 0;
  intensity_point_lights[2] = 0;
  intensity_ambient_light[0] = lights->amb_light->ambient * lights->amb_light->color.r / 255;
  intensity_ambient_light[1] = lights->amb_light->ambient * lights->amb_light->color.g / 255;
  intensity_ambient_light[2] = lights->amb_light->ambient * lights->amb_light->color.b / 255;
  get_color_sum_point_lights(obj_figure, lights->point_light, obj_params, intensity_point_lights);
  intensity_sum_lights[0] = intensity_ambient_light[0] + intensity_point_lights[0];
  intensity_sum_lights[1] = intensity_ambient_light[1] + intensity_point_lights[1];
  intensity_sum_lights[2] = intensity_ambient_light[2] + intensity_point_lights[2];
  color = get_final_color(&obj_params->color, intensity_sum_lights);
  return (color);
}