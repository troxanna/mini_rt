/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:06:53 by troxanna          #+#    #+#             */
/*   Updated: 2021/04/20 20:09:38 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

float				s_q(float a, float b, float c, float *t)
{
	float			discr;
	float			q;

	discr = b * b - 4 * a * c;
	if (discr < 0)
		return (65536);
	else if (discr == 0)
		t[0] = -0.5 * b / a;
	else
	{
		q = (b > 0) ? -0.5 * (b + sqrt(discr))
								: -0.5 * (b - sqrt(discr));
		t[0] = q / a;
		t[1] = c / q;
		if (t[0] < t[1] && t[0] > 0)
			return (t[0]);
		else if (t[1] < t[0] && t[1] > 0)
			return (t[1]);
		else
			return (65536);
	}
	return (t[0]);
}

int					ft_atoi(char *str, int *i)
{
	int				result;

	result = 0;
	if (str[*i] >= '0' && str[*i] <= '9')
	{
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			result = result * 10 + (str[*i] - '0');
			(*i)++;
		}
		return (result);
	}
	else
		return (-1);
}

void				ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	while (n--)
	{
		*tmp = 0;
		tmp++;
	}
}

int					close_window(void)
{
	exit(0);
}
