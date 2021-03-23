/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:34:35 by troxanna          #+#    #+#             */
/*   Updated: 2021/03/21 17:34:36 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_resolution       *parser_resolution(char *line, int i, t_scene *scene)
{
    int             width;
    int             height;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if ((width = ft_atoi(line, &i)) == -1)
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if ((height = ft_atoi(line, &i)) == -1)
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    scene->resolution = new_resolution(width, height);
    return (scene->resolution);
}

static t_amb_light       *parser_ambient(char *line, int i, t_scene *scene)
{
    float           brightness;
    float           *tmp;
    t_rgb           color_amb;

    brightness = 0;
    tmp = NULL;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if ((!(tmp = (ft_atof(line, &i, &brightness))) || (!(brightness >= 0 && brightness <= 1))))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atorgb(&color_amb, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    scene->amb_light = new_ambient_light(brightness, color_amb);
    return (scene->amb_light);
}

static t_camera       *parser_camera(char *line, int i, t_scene *scene)
{

    t_vector        view_point;
    t_vector        direction;
    float           fov;
    float           *tmp;
    tmp = NULL;
    fov = 0;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&view_point, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec_norm(&direction, line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(tmp = ft_atof(line, &i, &fov)) || !(fov >= 0 && fov <= 180))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_camera(scene, new_camera(view_point, direction, fov));
    return (scene->camera);
}

static t_point_light      *parser_light_point(char *line, int i, t_scene *scene)
{

    t_vector     position_light_point;
    t_rgb        color_light_point;
    float        brightness;
    float        *tmp;

    tmp = NULL;
    brightness = 0;
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atovec(&position_light_point,line, &i)))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(tmp = ft_atof(line, &i, &brightness)) || !(brightness >= 0 && brightness <= 1))
        return (NULL);
    while (line[i] == ' ' || line[i] == '\t')
            i++;
    if (!(ft_atorgb(&color_light_point, line, &i)))
        return (NULL);
    while (line[i] != '\0')
    {
        if (line[i] != ' ' && line[i] != '\t')
            return (NULL);
        i++;
    }
    add_point_light(scene, new_light(position_light_point, brightness, color_light_point));
    //free(color_light_point);
    return (scene->point_light);
}

int		parser_object_scene(char *line, t_scene *scene)
{
	int i;

    i = 0;
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (line[i] == 'R')
    {
        if (scene->resolution != NULL || !(scene->resolution = parser_resolution(line, ++i, scene)))
            return (-1);
    }
    else if (line[i] == 'A')
    {
        if (scene->amb_light != NULL || !(scene->amb_light = parser_ambient(line, ++i, scene)))
            return (-1);
    }
    else if (line[i] == 'c' && line[i + 1] != 'y')
    {
        if (!(scene->camera = parser_camera(line, ++i, scene)))
            return (-1);
    }
    else if (line[i] == 'l')
    {
        if (!(scene->point_light = parser_light_point(line, ++i, scene)))
            return (-1);
    }
    else
        i = parser_object_figure(i, line, scene);
    return (i);
}
