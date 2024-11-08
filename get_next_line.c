/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/08 17:07:47 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	return (bytes_r);
}

char	*get_next_line(int fd)
{
	static char	*draft;
	char		*buffer;
	char		*line;
	int			bytes_r;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_r = 1;
	bytes_r = copy_cat(fd, buffer, &draft, bytes_r);
	free(buffer);
	line = line_extraction(&draft, bytes_r);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// --------------MAIN TO DELETE-- -----
int	main(void)
{
	char *line;
	int fd;
	int i;

	// fd = open("crevette.txt", O_RDONLY);
	// printf("%d", fd);
	// i = 0;
	while ((line = get_next_line(0)) != NULL)
	{
		printf("%s", line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}