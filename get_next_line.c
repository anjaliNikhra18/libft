/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneekhra <aneekhra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 00:37:18 by aneekhra          #+#    #+#             */
/*   Updated: 2023/12/11 16:36:02 by aneekhra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *base_buffer)
{
	char	*new_buffer;
	char	*temp;
	int		read_bytes;

	new_buffer = (char *) malloc((sizeof(char)) * (BUFFER_SIZE + 1));
	if (!new_buffer)
		return (NULL);
	read_bytes = 1;
	while ((!ft_strchr(base_buffer, '\n')) && (read_bytes != 0))
	{
		read_bytes = read(fd, new_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(new_buffer), free(base_buffer), NULL);
		new_buffer[read_bytes] = '\0';
		temp = ft_strjoin(base_buffer, new_buffer);
		free(base_buffer);
		base_buffer = temp;
	}
	return (free(new_buffer), base_buffer);
}

char	*print_line(char *base_buffer, int i)
{
	char	*str;

	if (!base_buffer[i])
		return (NULL);
	while (base_buffer[i] && base_buffer[i] != '\n')
		i++;
	if (base_buffer[i] == '\n')
		i++;
	str = (char *)malloc((sizeof(char)) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (base_buffer[i] && base_buffer[i] != '\n')
	{
		str[i] = base_buffer[i];
		i++;
	}
	if (base_buffer[i] == '\n')
	{
		str[i] = base_buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_save_string(char *base_buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (base_buffer[i] && base_buffer[i] != '\n')
		i++;
	if (!base_buffer[i])
		return (free(base_buffer), NULL);
	str = (char *)malloc((ft_strlen(base_buffer) - i + 1) * sizeof(char));
	if (!str)
		return (free(base_buffer), NULL);
	i++;
	j = 0;
	while (base_buffer[i])
		str[j++] = base_buffer[i++];
	str[j] = '\0';
	return (free(base_buffer), str);
}

char	*get_next_line(int fd)
{
	static char	*base_buffer;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!base_buffer)
		base_buffer = ft_strdup("");
	base_buffer = ft_read(fd, base_buffer);
	if (!base_buffer)
		return (NULL);
	line = print_line(base_buffer, i);
	base_buffer = ft_save_string(base_buffer);
	return (line);
}

 int main()
{
	int fd;
	char *next_line;
	int count;
	count = 0;
	fd = open("textfile.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("error in opening");
		return (1);
	}
	while (fd)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break;
		count++;
		printf("[%d]:%s\n",count,next_line);
		free (next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
} 