#include "../../includes/minirt.h"

static void    init_ray_tracing(t_scene *scene, t_object_figure *object_figure)
{
    object_figure->plane = scene->plane;
    object_figure->sphere = scene->sphere;
    object_figure->triangle = scene->triangle;
    object_figure->square = scene->square;
    object_figure->cylinder = scene->cylinder;
    object_figure->ray_orig = &(scene->camera->origin);
}


static t_vector    *new_ray(t_scene *scene, int pixel_x, int pixel_y)
{
    t_vector       *ray;
    float           ray_x; 
    float           ray_y;
    float           scale;
    t_vector        tmp_ray;

    scale = tan(scene->camera->fov / 2 * M_PI / 180);
    ray_x = (2 * ((pixel_x + 0.5) / (float)scene->resolution->width) - 1) * scale * ((float)scene->resolution->width / (float)scene->resolution->height);
    ray_y = (1 - 2 * ((pixel_y + 0.5) / (float)scene->resolution->height)) * scale; 
    init_vector(&tmp_ray, ray_x, ray_y, -1);
    ray = matrix_to_world(&tmp_ray, &(scene->camera->direction));
    vector_normalize(ray);
    return (ray);
}



void    ray_tracing(void *mlx, void *window, t_scene scene)
{
    t_object_params     object_params;
    t_object_figure     object_figure;
    t_vector            *ray_dir;
    float               pixel_x;
    float               pixel_y;
    int                 color;
    
    init_ray_tracing(&scene, &object_figure);
    pixel_x = 0;
    pixel_y = 0;
    while (pixel_y < scene.resolution->height)
    {
        pixel_x = 0;
        while (pixel_x < scene.resolution->width)
        {
            ray_dir = new_ray(&scene, pixel_x, pixel_y);
            if (intersect_object(&object_params, &object_figure, ray_dir))
            {
                color = create_trgb(0, object_params.color.r, object_params.color.g, object_params.color.b);
                //color = get_light_point(scene->object, &object_params);
            }
            else
                color = create_trgb(0, 0, 0, 0);
            free(ray_dir);
            mlx_pixel_put(mlx, window, pixel_x, pixel_y, color);
            pixel_x++;
        }
        pixel_y++;
    }
}