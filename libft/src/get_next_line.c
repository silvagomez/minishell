/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 12:50:45 by edejimen          #+#    #+#             */
/*   Updated: 2023/06/12 16:15:55 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_new_remain(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0' || line[1] == '\0')
		return (0);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (backup[0] == '\0')
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*read_to_remain(int fd, char *buff, char *remain)
{
	int		rd;
	char	*temp;

	rd = 1;
	while (rd != '\0')
	{
		rd = read(fd, buff, BUFFER_SIZE);
		if (rd == -1)
			return (free(remain), NULL);
		else if (rd == 0)
			break ;
		buff[rd] = '\0';
		if (!remain)
			remain = ft_strdup("");
		temp = remain;
		if (temp && buff)
			remain = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr (buff, '\n'))
			break ;
	}
	return (remain);
}

char	*get_next_line(int fd)
{
	static char	*remain[4096];
	char		*buff;
	char		*line[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	line[fd] = read_to_remain(fd, buff, remain[fd]);
	if (!line[fd])
		remain[fd] = 0;
	free(buff);
	buff = NULL;
	if (!line[fd])
		return (NULL);
	remain[fd] = ft_new_remain(line[fd]);
	return (line[fd]);
}
