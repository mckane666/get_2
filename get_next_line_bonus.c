/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhenriqu <jhenriqu@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:24:42 by jhenriqu          #+#    #+#             */
/*   Updated: 2021/02/17 21:57:37 by jhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*cutnew(char *new_line, char **line)
{
	char	*tempo;
	int		len;

	len = 0;
	if (new_line == NULL)
	{
		*line = ft_strdup("");
		return (NULL);
	}
	while (new_line[len] != '\n' && new_line[len] != '\0')
		len++;
	if (new_line[len] == '\n')
	{
		*line = ft_substr(new_line, 0, len);
		tempo = ft_strdup(&new_line[len + 1]);
		free(new_line);
		new_line = tempo;
	}
	else if (new_line[len] == '\0')
	{
		*line = ft_strdup(new_line);
		free(new_line);
		new_line = NULL;
	}
	return (new_line);
}

int		r_result(char *new_line, int r, int check)
{
	if (r < 0)
		return (-1);
	if ((r == 0 && (!new_line || ft_strchr(new_line, '\0'))) && !check)
		return (0);
	return (1);
}

char	*thanku_norm(char *buf, char *new_line)
{
	char*temp;

	temp = ft_strjoin(new_line, buf);
	free(new_line);
	new_line = temp;
	return (new_line);
}

int		free_or_not2_free(char **buf, char **line, int fd)
{
	*buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!(*buf) || (fd < 0 || fd == 1 || fd == 2 || !line
				|| BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1))
	{
		if (*buf)
			free(*buf);
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	t_gnl		next;
	static char	*new_line[1024];

	next.check = 0;
	if (!free_or_not2_free(&next.buf, line, fd))
		return (-1);
	next.r = read(fd, next.buf, BUFFER_SIZE);
	while (next.r > 0)
	{
		next.buf[next.r] = '\0';
		if (!new_line[fd])
			new_line[fd] = ft_strdup(next.buf);
		else
			new_line[fd] = thanku_norm(next.buf, new_line[fd]);
		if (ft_strchr(next.buf, '\n'))
			break ;
		next.r = read(fd, next.buf, BUFFER_SIZE);
	}
	free(next.buf);
	if (ft_strchr(new_line[fd], '\n'))
		next.check = 1;
	new_line[fd] = cutnew(new_line[fd], line);
	return (r_result(new_line[fd], next.r, next.check));
}
