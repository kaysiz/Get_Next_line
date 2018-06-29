/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksiziva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 09:59:01 by ksiziva           #+#    #+#             */
/*   Updated: 2018/06/29 17:15:29 by ksiziva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_line(char **save, char ***line)
{
	int		x;
	char	*sub;

	if (ft_strchr(*save, '\n'))
	{
		x = 0;
		while (save[0][x] != '\n')
			x++;
		**line = ft_strcat(**line, ft_strsub(*save, 0, x));
		sub = ft_strchr(*save, '\n');
		*save = ft_strdup(sub) + 1;
		return (1);
	}
	else
	{
		**line = ft_strcat(**line, *save);
	}
	return (0);
}

int		read_text(int fd, char **line)
{
	char			buff[BUFF_SIZE + 1];
	static	char	*save = "";
	char			*sub;
	int				x;
	int				ret;

	if (get_line(&save, &line) == 1)
		return (1);
	while ((ret = read(fd, buff, BUFF_SIZE)))
	{
		buff[ret] = '\0';
		if (ft_strchr(buff, '\n'))
		{
			x = 0;
			while (buff[x] != '\n')
				x++;
			*line = ft_strcat(*line, ft_strsub(buff, 0, x));
			sub = ft_strchr(buff, '\n');
			save = ft_strdup(sub) + 1;
			return (1);
		}
		else
			*line = ft_strcat(*line, buff);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	int		x;
	char	*str;

	str = "";
	if (str)
		ft_bzero(str, ft_strlen(str));
	if (fd < 0)
		return (-1);
	x = read_text(fd, &str);
	*line = str;
	if (ft_strlen(str) > 0)
		return (1);
	if (x == 0)
		free(*line);
	return (x);
}
