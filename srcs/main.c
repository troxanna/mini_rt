#include "../includes/minirt.h"


// int     main(void)
// {
//    // void    *mlx;
//     //void    *window;


//     //mlx = mlx_init();
    
//     //window = mlx_new_window(mlx, 900, 650, "miniRT");
    
//     //free_scene
//     //mlx_loop(mlx);

//     return (0);
// }

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     main(int argc, char **argv)
{
    void        *mlx_ptr;
    void        *window;
    t_scene     scene;
    t_data      img;

    if (argc == 2)
    {
        if (!(parser_rt(argv[1], mlx_ptr, &scene)))
            ft_error(2);
        mlx_ptr = mlx_init();
        window = mlx_new_window(mlx_ptr, scene.resolution->width, scene.resolution->height, "miniRT");
        img.img = mlx_new_image(mlx_ptr, scene.resolution->width, scene.resolution->height);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
        ray_tracing(&img, scene);
        mlx_put_image_to_window(mlx_ptr, window, img.img, 0, 0);
        //free_scene
        mlx_loop(mlx_ptr);
        return (1);
    }
    else
        return (0);
}