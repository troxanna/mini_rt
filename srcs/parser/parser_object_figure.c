#include "../../includes/minirt.h"

static t_sphere       *parser_sphere(char *line, int i, t_scene *scene)
{

    t_vector     sphere_center;
    t_rgb        color_sphere;
    float        diameter;
    float        *tmp;

    tmp = NULL;
    diameter = 0;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&sphere_center, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(tmp = ft_atof(line, &i, &diameter)) || diameter < 0)
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atorgb(&color_sphere, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_sphere(scene, new_sphere(sphere_center, diameter / 2, color_sphere));
    return (scene->sphere);
}

static t_triangle       *parser_triangle(char *line, int i, t_scene *scene)
{
    t_vector     first_point;
    t_vector     second_point;
    t_vector     third_point;
    t_rgb        color_triangle;

    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&first_point, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&second_point, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&third_point, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atorgb(&color_triangle, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_triangle(scene, new_triangle(first_point, second_point, third_point, color_triangle));
    return (scene->triangle);
}

static t_plane       *parser_plane(char *line, int i, t_scene *scene)
{
    t_vector     point_plane;
    t_vector     direction;
    t_rgb        color_plane;

    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&point_plane, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec_norm(&direction, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
   if (!(ft_atorgb(&color_plane, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_plane(scene, new_plane(point_plane, direction, color_plane));
    return (scene->plane);
}

static t_square       *parser_square(char *line, int i, t_scene *scene)
{
    t_vector    center_square;
    t_vector    direction;
    float       side;
    t_rgb       color_square;
    float       *tmp;
    
    tmp = NULL;
    side = 0;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&center_square, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec_norm(&direction, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(tmp = ft_atof(line, &i, &side)) || side < 0)
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;  
    if (!(ft_atorgb(&color_square, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_square(scene, new_square(center_square, direction, side, color_square));
    return (scene->square);
}

static t_cylinder       *parser_cylinder(char *line, int i, t_scene *scene)
{
    t_vector    point_cylinder;
    t_vector    direction;
    float       size[2];
    t_rgb       color_cylinder;
    float        *tmp;
    
    tmp = NULL;
    size[0] = 0;
    size[1] = 0;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&point_cylinder, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec_norm(&direction, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(tmp = ft_atof(line, &i, &size[0])) || size[0] < 0)
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(tmp = ft_atof(line, &i, &size[1])) || size[1] < 0)
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;  
   if (!(ft_atorgb(&color_cylinder, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_cylinder(scene, new_cylinder(point_cylinder, direction, size[0], size[1], color_cylinder));
    return (scene->cylinder);
}


int		parser_object_figure(int i, char *line, t_scene *scene)
{
    if (line[i] == 's' && line[i + 1] == 'p')
    {
        i++;
        if (!(scene->sphere = parser_sphere(line, ++i, scene)))
            return (-1); 
    }
    else if (line[i] == 't' && line[i + 1] == 'r')
    {
        i++;
        if (!(scene->triangle = parser_triangle(line, ++i, scene)))
            return (-1);
    }
    else if (line[i] == 'p' && line[i + 1] == 'l')
    {
        i++;
        if (!(scene->plane = parser_plane(line, ++i, scene)))
            return (-1);
    }
    else if (line[i] == 's' && line[i + 1] == 'q')
    {
        i++;
        if (!(scene->square = parser_square(line, ++i, scene)))
            return (-1);
    }
    else if (line[i] == 'c' && line[i + 1] == 'y')
    {
        i++;
        if (!(scene->cylinder = parser_cylinder(line, ++i, scene)))
            return (-1);
    }
    else
        return (-1);
    return (i);
}