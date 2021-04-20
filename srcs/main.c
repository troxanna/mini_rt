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


int     mlx_action_window(int keycode, t_mlx *vars)
{
    printf("%d\n", keycode);
    if (keycode == 53)
        exit (0);
    if (keycode == 123)
    {
        mlx_destroy_image(vars->mlx, vars->img);
        mlx_destroy_window(vars->mlx, vars->win);
    }
    // if (keycode == 124)
    // {

    // }
    //mlx_destroy_window(vars->mlx, vars->win);

}

int     main(int argc, char **argv)
{
    t_mlx   mlx;
    t_scene     scene;
    t_data      img;

    if (argc == 2)
    {
        if (!(parser_rt(argv[1], mlx.mlx, &scene)))
            ft_error(2);
        mlx.mlx = mlx_init();
        mlx.win = mlx_new_window(mlx.mlx, scene.resolution->width, scene.resolution->height, "miniRT");
        img.img = mlx_new_image(mlx.mlx, scene.resolution->width, scene.resolution->height);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
        ray_tracing(&img, scene);
        mlx.img = &img;
        mlx.camera = scene.camera;
        mlx_hook(mlx.win, 2, 1L<<0, mlx_action_window, &mlx);
        mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
        mlx_loop(mlx.mlx);
        return (1);
    }
    else
        return (0);
}