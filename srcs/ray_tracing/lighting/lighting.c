#include "../../../includes/minirt.h"

static int     angle_between_norm_and_light(t_vector *norm, t_vector *L)
{
  float dot;

  dot = vector_dot_products(norm, L);
  if (dot >= 0)
    return (0);
  else
    return (1);
  // float   len_NL;
  // float   cos;
  // float   angle;

  // len_NL = vector_length(norm) * vector_length(L);
  // cos = vector_length(L) / len_NL;
  // angle = acos(cos) * 180 / M_PI;
  // if (angle > 90)
  //   return (1);
  // else
  //   return (0);

}

static void      reverse_normal(t_vector *norm)
{
  if (norm->x < 0)
    norm->x = norm->x * (-1);
  if (norm->y < 0)
    norm->y = norm->y * (-1);
  if (norm->z < 0)
    norm->z = norm->z * (-1);
}

static int     shadow_check(t_object_figure *obj_figure, t_vector *L, t_vector *intersect_point)
{
  float   range_t[3];
  t_object_params object_params_tmp;
  // object_params_tmp.flag = 0;
  // object_params_tmp.intersect_point.x = 0;
  // object_params_tmp.intersect_point.y = 0;
  // object_params_tmp.intersect_point.z = 0;
  // object_params_tmp.color.r = 0;
  // object_params_tmp.color.g = 0;
  // object_params_tmp.color.b = 0;
  // object_params_tmp.norm.x = 0;
  // object_params_tmp.norm.y = 0;
  // object_params_tmp.norm.z = 0;

  float    closest_t;
  range_t[0] = 0;
  range_t[1] = 0.000000001;
  range_t[2] = 0.9999;
  closest_t = 0;
  t_vector ptr;
  //vector_normalize(L);

  //init_vector(&ptr, intersect_point->x, intersect_point->y, intersect_point->z);
  // t_vector    tmp_inter;
  // init_vector(&tmp_inter, )
  //range_t[2] = 0.9999;
  //printf("%p\n", &(obj_figure->triangle));
  //делать проверку диапазона в этой функции
  if (obj_figure->sphere && (closest_t = iterate_object_sphere(obj_figure->sphere, &object_params_tmp, L, intersect_point)))
  {
      //range_t[1] = 0.001;
      if (closest_t > range_t[1] && closest_t < range_t[2])
      {
        //printf("test");
        return (1);
      }
  }
  if (obj_figure->triangle && (closest_t = iterate_object_triangle(obj_figure->triangle, &object_params_tmp, L, intersect_point)))
  {
      if (closest_t > range_t[1] && closest_t < (range_t[2]))
      {
        return (1);
      }
  }
  if (obj_figure->square && (closest_t = iterate_object_square(obj_figure->square, &object_params_tmp, L, intersect_point)))
  {
      if (closest_t > range_t[1] && closest_t < range_t[2])
      {
        //printf("test");
        return (1);
      }
  }
  if (obj_figure->cylinder && (closest_t = iterate_object_cylinder(obj_figure->cylinder, &object_params_tmp, L, intersect_point)))
  {
      if (closest_t > range_t[1] && closest_t < range_t[2])
      {
        //printf("\x1B[31mtest\x1B[0m");
        return (1);
      }
  }
  if (obj_figure->plane && (closest_t = iterate_object_plane(obj_figure->plane, &object_params_tmp, L, intersect_point)))
  {
      if (closest_t > range_t[1] && closest_t < range_t[2])
      {
        //printf("test");
        return (1);
      }
  }
  // if (obj_figure->triangle && iterate_object_triangle(obj_figure->triangle, &object_params_tmp, L, intersect_point, range_t))
  //     return (1);
  // if (obj_figure->plane && iterate_object_plane(obj_figure->plane, &object_params_tmp, L, intersect_point, range_t));
  //     return (1);
  return (0);
}

static void    add_intensity_point_light(float *intensity, t_point_light *light, float dot_NL)
{
    intensity[0] = intensity[0] + light->brightness * light->color.r / 255 * (dot_NL);
    intensity[1] = intensity[1] + light->brightness * light->color.g / 255 * (dot_NL);
    intensity[2] = intensity[2] + light->brightness * light->color.b / 255 * (dot_NL);
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
  t_vector          tmp_norm;
  t_vector          tmp_L;
  int angle = 0;


  t = 0;
  tmp = 0;
  ptr = point_lights;

  while (ptr)
  {
    tmp = 0;
    vector_subtraction(&L, &(ptr->point_light), &(obj_params->intersect_point));
    //vector_normalize(&L);
    //так как для поиска тени нам нужна не нормализованная длина L, то оставляем ее не нормализованной
    if (angle_between_norm_and_light(&(obj_params->norm), &L))
    {
      angle = 1;
      if ((obj_params->flag == 1) && angle == 1)
        reverse_normal(&(obj_params->norm));
      if (obj_params->flag == 0)
        tmp = 1;
      else
        tmp = 0;
    }
    // init_vector(&tmp_norm, obj_params->norm.x, obj_params->norm.y, obj_params->norm.z);
    // init_vector(&tmp_L, L.x, L.y, L.z);
    // else if (NL < 0 && obj_params->flag)
    // {
    //     //obj_params->norm.z = obj_params->norm.z * (-1);
    //     scalars_mult_vectors(-1, &(obj_params->norm));
    //     NL = vector_dot_products(&(obj_params->norm), &L);
    // }
    tmp = shadow_check(obj_figure, &L, &(obj_params->intersect_point));
    if (tmp == 0)
    {
      //init_vector(&tmp_norm, obj_params->norm.x, obj_params->norm.y, obj_params->norm.z);
      //vector_normalize(&tmp_L);
      vector_normalize(&L);
      NL = vector_dot_products(&(obj_params->norm), &L);
      add_intensity_point_light(intensity, ptr, NL);
    }
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
  if (intensity_point_lights[0] < 0 || intensity_point_lights[1] < 0 || intensity_point_lights[2] < 0)
  {
    intensity_sum_lights[0] = intensity_ambient_light[0];
    intensity_sum_lights[1] = intensity_ambient_light[1];
    intensity_sum_lights[2] = intensity_ambient_light[2];
  }
  else
  {
    intensity_sum_lights[0] = intensity_ambient_light[0] + intensity_point_lights[0];
    intensity_sum_lights[1] = intensity_ambient_light[1] + intensity_point_lights[1];
    intensity_sum_lights[2] = intensity_ambient_light[2] + intensity_point_lights[2];
  }
  // intensity_sum_lights[0] = intensity_ambient_light[0] + intensity_point_lights[0];
  // intensity_sum_lights[1] = intensity_ambient_light[1] + intensity_point_lights[1];
  // intensity_sum_lights[2] = intensity_ambient_light[2] + intensity_point_lights[2];
  color = get_final_color(&obj_params->color, intensity_sum_lights);
  return (color);
}
