/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-m <aecm.davidgomez@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 17:18:53 by dgomez-m          #+#    #+#             */
/*   Updated: 2024/01/02 00:47:41 by dgomez-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero_gnl(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = 0;
}

char	*read_line(int fd, char *buf)
{
	char	*line;
	int		countread;

	line = ft_strdup_gnl(buf);
	while (!(ft_strchr_gnl(line, '\n')))
	{
		countread = read(fd, buf, BUFFER_SIZE);
		if (countread == -1)
		{
			free(line);
			ft_bzero_gnl(buf, BUFFER_SIZE + 1);
			return (NULL);
		}
		if (countread == 0)
			break ;
		buf[countread] = '\0';
		line = ft_strjoin(line, buf, countread);
	}
	return (line);
}

void	prepare_buffer(char *buf, char *line, char *newline)
{
	int	to_copy;

	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strlcpy_gnl(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		to_copy = ft_strlen_gnl(line);
		ft_strlcpy_gnl(buf, "", BUFFER_SIZE + 1);
	}
	line[to_copy] = '\0';
}

int	get_next_line(int fd, char **out_line)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		*newline;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (EXIT_FAILURE);
	line = read_line(fd, buf[fd]);
	if (!line || ft_strlen_gnl(line) == 0)
		return (free(line), EXIT_FAILURE);
	newline = ft_strchr_gnl(line, '\n');
	prepare_buffer(buf[fd], line, newline);
	*out_line = line;
	return (EXIT_SUCCESS);
}
