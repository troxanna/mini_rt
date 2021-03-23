#include "../../includes/minirt.h"

t_rgb    *new_color(int r, int g, int b)
{
    t_rgb    *color;
    if (!(color = malloc(sizeof(t_rgb))))
        ft_error(1);
    color->r = r;
    color->g = g;
    color->b = b;
    return (color);
}

void   init_color(t_rgb *color, int r, int g, int b)
{
    color->r = r;
    color->g = g;
    color->b = b;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}
