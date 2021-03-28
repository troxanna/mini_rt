#include "../../../includes/minirt.h"

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
    //scalars_mult_vectors(0.003, light_object->norm);
    NL = vector_dot_products(&(obj_params->norm), &L);
    if (NL < 0)
        NL = 0;
    
    //add_intensity_point_light(intensity, ptr, NL);
    // while (ptr_sphere)
    // {
    //   //printf("%f\n", t);
    //   //умнржить L на 0,01
    //     if (((sphere_intersect(light_object->intersect_point, L, &t, ptr_sphere)) > 0))
    //     {
    //       //printf ("%f\n", t);
    //       //добавить проверку, когда один объект перекрывает другой
    //         if (t > 0.1)
    //           tmp = 1;
    //     }
    //     ptr_sphere = ptr_sphere->next;
    // }
    // while (ptr_triangle)
    // {
    //   //умнржить L на 0,01
    //     if (((triangle_intersect(light_object->intersect_point, L, &t, ptr_sphere)) > 0))
    //     {
    //         if (t > 0.1)
    //           tmp = 1;
    //     }
    //     ptr_sphere = ptr_sphere->next;
    // }
    if (tmp != 1)
      add_intensity_point_light(intensity, ptr, NL);
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

  vector_normalize(&(obj_params->norm));
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