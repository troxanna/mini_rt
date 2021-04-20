/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ato_pars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 19:29:42 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/20 20:03:27 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float			*ft_atof(char *str, int *i, float *result)
{
	float		point_zero;
	float		nb;
	int			sign;

	sign = 1;
	point_zero = 0.1;
	if (str[*i] == '-')
	{
		sign = -1;
		(*i)++;
	}
	if (str[*i] >= '0' && str[*i] <= '9')
		nb = ft_atoi(str, i);
	else
		return (NULL);
	*result = nb;
	if (str[*i] == '.')
	{
		(*i)++;
		if (str[*i] >= '0' && str[*i] <= '9')
		{
			while (str[*i] >= '0' && str[*i] <= '9')
			{
				*result = *result + (point_zero * (str[*i] - '0'));
				point_zero *= 0.1;
				(*i)++;
			}
		}
		else
			return (NULL);
	}
	if (sign < 0)
		*result = *result * (-1);
	return (result);
}

int				ft_atorgb(t_rgb *color, char *str, int *i)
{
	int			rgb[3];

	rgb[0] = ft_atoi(str, i);
	if (!(rgb[0] >= 0 && rgb[0] <= 255) || str[*i] != ',')
		return (0);
	(*i)++;
	rgb[1] = ft_atoi(str, i);
	if (!(rgb[1] >= 0 && rgb[1] <= 255) || str[*i] != ',')
		return (0);
	(*i)++;
	rgb[2] = ft_atoi(str, i);
	if (!(rgb[2] >= 0 && rgb[2] <= 255))
		return (0);
	init_color(color, rgb[0], rgb[1], rgb[2]);
	return (1);
}

int				ft_atovec(t_vector *result, char *str, int *i)
{
	float		*tmp;
	float		vec[3];

	if (!(tmp = ft_atof(str, i, vec)) || str[*i] != ',')
		return (0);
	(*i)++;
	if (!(tmp = ft_atof(str, i, vec + 1)) || str[*i] != ',')
		return (0);
	(*i)++;
	if (!(tmp = ft_atof(str, i, vec + 2)))
		return (0);
	init_vector(result, vec[0], vec[1], vec[2]);
	return (1);
}

int				ft_atovec_norm(t_vector *result, char *str, int *i)
{
	float		*tmp;
	float		vec[3];

	if (!(tmp = ft_atof(str, i, vec)) || str[*i] != ',')
		return (0);
	if (!(vec[0] >= -1 && vec[0] <= 1))
		return (0);
	(*i)++;
	if (!(tmp = ft_atof(str, i, vec + 1)) || str[*i] != ',')
		return (0);
	if (!(vec[1] >= -1 && vec[1] <= 1))
		return (0);
	(*i)++;
	if (!(tmp = ft_atof(str, i, vec + 2)))
		return (0);
	if (!(vec[2] >= -1 && vec[2] <= 1))
		return (0);
	init_vector(result, vec[0], vec[1], vec[2]);
	return (1);
}
