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

int     main(int argc, char **argv)
{
    void        *mlx_ptr;
    void        *window;
    t_scene     scene;

    if (argc == 2)
    {
        if (!(parser_rt(argv[1], mlx_ptr, &scene)))
            ft_error(2);
        mlx_ptr = mlx_init();
        window = mlx_new_window(mlx_ptr, scene.resolution->width, scene.resolution->height, "miniRT");
        ray_tracing(mlx_ptr, window, scene);
        //free_scene
        mlx_loop(mlx_ptr);
        return (1);
    }
    else
        return (0);
}