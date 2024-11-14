/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/11 12:21:52 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*arr;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	arr = malloc(s1_len + s2_len + 1);
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1, s1_len + 1);
	ft_strlcat(arr, s2, s2_len + s1_len + 2);
	return (arr);
}

static char	*endof_file(char **draft, char **line)
{
	*line = ft_strdup(*draft);
	free(*draft);
	*draft = NULL;
	return (*line);
}

static char	*line_extraction(char **draft, int bytes_r)
{
	size_t	line_len;
	char	*new_pos;
	char	*line;
	char	*temp;

	new_pos = ft_strchr(*draft, '\n');
	if (new_pos)
	{
		line_len = new_pos - *draft;
		line = malloc(line_len + 2);
		if (!line)
			return (NULL);
		ft_strlcpy(line, *draft, line_len + 2);
		temp = ft_strdup(new_pos + 1);
		free(*draft);
		*draft = temp;
		return (line);
	}
	else if (*draft && bytes_r == 0)
	{
		line = endof_file(draft, &line);
		return (line);
	}
	return (NULL);
}

static int	copy_cat(int fd, char *buffer, char **draft, int bytes_r)
{
	char	*temp;

	while (!ft_strchr(*draft, '\n') && bytes_r > 0)
	{
		bytes_r = read(fd, buffer, BUFFER_SIZE);
		if (bytes_r < 0)
		{
			free(*draft);
			*draft = NULL;
			free(buffer);
			return (0);
		}
		buffer[bytes_r] = '\0';
		if (*draft)
		{
			temp = ft_strjoin(*draft, buffer);
			free(*draft);
			*draft = temp;
		}
		else if (!(*draft))
			*draft = ft_strdup(buffer);
	}
	free(buffer);
	return (bytes_r);
}

char	*get_next_line(int fd)
{
	static char	*draft;
	char		*buffer;
	char		*line;
	int			bytes_r;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(draft);
		return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_r = 1;
	bytes_r = copy_cat(fd, buffer, &draft, bytes_r);
	line = line_extraction(&draft, bytes_r);
	if (line && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}
