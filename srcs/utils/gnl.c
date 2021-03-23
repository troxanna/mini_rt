/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: troxanna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:22:46 by troxanna          #+#    #+#             */
/*   Updated: 2021/03/21 17:33:42 by troxanna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int		ft_strlen(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char		*join_char(char *str, char ch)
{
	char		*str_main;
	int			i;

	i = 0;
	if (str == NULL)
	{
		str_main = (char *)malloc(sizeof(char) * 2);
		str_main[0] = ch;
		str_main[1] = '\0';
		return (str_main);
	}
	if ((str_main = (char *)malloc(sizeof(char) * ft_strlen(str) + 2)))
	{
		while (str[i])
		{
			str_main[i] = str[i];
			i++;
		}
		str_main[i] = ch;
		str_main[i + 1] = '\0';
		free(str);
		return (str_main);
	}
	return (NULL);
}

int				get_line(int fd, char **line)
{
	char		ch;
	int			read_b;

	read_b = 1;
	*line = NULL;
	while ((read_b = read(fd, &ch, 1)))
	{
		if (ch == '\n')
			return (1);
		*line = join_char(*line, ch);
	}
	if (read_b == -1)
		return (-1);
	return (0);
}
