/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisux <lisux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/05 11:43:08 by lisux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	find_line(char *buffer)
{
	int	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (-42);
}
char	*line_extraction(char **static_var, int bytes_r)
{
	char	*new_pos;
	char	*line;
	size_t	line_len;
	char	*content_left;

	new_pos = ft_strchr(*static_var, '\n');
	if (new_pos)
	{
		line_len = new_pos - *static_var;
		line = calloc(line_len + 1);
		if (!line)
			return (NULL);
		line = ft_strlcpy(line, *static_var, line_len + 1);
		content_left = ft_strdup(new_pos + 1);
		free(*static_var);
		*static_var = content_left;
	}
	else if (bytes_r == 0)
	{
		line = ft_strdup(*static_var);
		free(*static_var);
		*static_var = NULL;
	}
	else
		line = NULL;
	return (line);
}
char	*get_next_line(int fd)
{

}
int	main(void)
{
	int			fd;
	static char	buffer[BUFFER_SIZE + 1];
	int			bytes_r;

	fd = open("salut.txt", O_RDONLY);
	bytes_r = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_r] = '\0';
	printf("%s", buffer);
	close(fd);

}
