/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 00:39:40 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/21 00:40:42 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void					while_parse(int *i, char *line)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

t_cylinder				*parser_cylinder(char *line, int i, t_scene *scene,
																	float *tmp)
{
	t_vector			cylinder[2];
	float				size[2];
	t_rgb				color_cylinder;

	while_parse(&i, line);
	if (!(ft_atovec(cylinder, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atovec_norm(cylinder + 1, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (!(tmp = ft_atof(line, &i, &size[0])) || size[0] < 0)
		return (NULL);
	while_parse(&i, line);
	if (!(tmp = ft_atof(line, &i, &size[1])) || size[1] < 0)
		return (NULL);
	while_parse(&i, line);
	if (!(ft_atorgb(&color_cylinder, line, &i)))
		return (NULL);
	while_parse(&i, line);
	if (line[i] != '\0')
		return (NULL);
	add_cylinder(scene, new_cylinder(cylinder[0],
					cylinder[1], size, color_cylinder));
	return (scene->cylinder);
}
