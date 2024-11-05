/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/05 17:12:08 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return ((char *)ptr - (char *)str);
}
char	*ft_strchr(const char *s, int c)
{
	const char	*str;
	int			i;

	str = s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)str + i);
	return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (!size)
		return (src_len);
	if (dest_len >= size)
		return (src_len + size);
	i = 0;
	while (src[i] && dest_len + i < size - 1)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = ft_strlen(src);
	i = 0;
	if (dst == NULL || src == 0)
		return (0);
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
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

char	*line_extraction(char **draft, int bytes_r)
{
	size_t	line_len;
	char	*new_pos;
	char	*line;

	new_pos = ft_strchr(*draft, '\n');
	if (new_pos)
	{
		line_len = new_pos - *draft;
		line = malloc(line_len + 1);
		if (!line)
			return (NULL);
		ft_strlcpy(line, *draft, line_len + 1);
		*draft = NULL;
		*draft = new_pos + 1;
		return (line);
	}
	else if (bytes_r == 0)
	{
		return (*draft);
	}
	else
	{
		line = NULL;
		return (line);
	}
}
char	*get_next_line(int fd)
{
	static char	*draft;
	char		*buffer;
	char		*line;
	int			bytes_r;

	while ((bytes_r = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_r + 1] = '\0';
		draft = ft_strjoin(draft, buffer);
		line = line_extraction(&draft, bytes_r);
		return (line);
	}
	return (NULL);
}
int	main(void)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	int		fd;

	// int		bytes_r;
	fd = open("salut.txt", O_RDONLY);
	/*
	bytes_r = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_r] = '\0';
	printf("%s", buffer);*/
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
}
