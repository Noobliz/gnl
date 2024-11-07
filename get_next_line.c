/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiet <lguiet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:36:14 by lguiet            #+#    #+#             */
/*   Updated: 2024/11/07 16:32:03 by lguiet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		line = ft_strdup(*draft);
		free(*draft);
		*draft = NULL;
		return (line);
	}
	return (NULL);
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
	while (!ft_strchr(draft, '\n') && bytes_r > 0)
	{
		bytes_r = read(fd, buffer, BUFFER_SIZE);
		if (bytes_r == -1)
		{
			free(draft);
			draft = NULL;
		}
		if (bytes_r < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_r] = '\0';
		if (draft) // si y'a déjà qqchose dans draft, on y ajoute le buffer
		{
			temp = ft_strjoin(draft, buffer);
			free(draft);
			draft = temp;
		}
		else if (!draft)
			draft = ft_strdup(buffer);
	}
	free(buffer); // on free une fois copié et ligne trouvée ou fin du fichier
	line = line_extraction(&draft, bytes_r);
	// if (bytes_r == 0 && draft != NULL || bytes_r > 0)
	// {
	// 	return (line);
	// }
	// else if (bytes_r == 0)
	// 	free(line);
	//  return (NULL);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

// --------------MAIN TO DELETE-- -----
// int	main(void)
// {
// 	char *line;
// 	int fd;
// 	int i;

// 	fd = open("salut.txt", O_RDONLY);
// 	i = 0;
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("line %d : %s", i + 1, line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }