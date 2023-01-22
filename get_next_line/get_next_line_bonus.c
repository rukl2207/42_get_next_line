/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:56:05 by scornhol          #+#    #+#             */
/*   Updated: 2021/11/04 14:56:45 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Function name: get_next_line
 * Prototype: char *get_next_line(int fd);
 * Turn in files: get_next_line.c, get_next_line_utils.c, get_next_line.h
 * Parameters: File descriptor to read from
 * Return value: Read line:  correct behavior
 * 				 NULL: nothing else to read or an error occurred
 * External functs.: read, malloc, free
 * Description: Write a function which returns a line read from
 * 				a file descriptor								 */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (s2 && !s1)
		return (ft_strdup(s2));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (NULL == str)
		return (NULL);
	ft_strlcpy(str, s1, len_s1 + 1);
	ft_strlcat(str + len_s1, s2, len_s2 + 1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	sub_len;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	sub_len = ft_strlen(s + start);
	if (sub_len < len)
		len = sub_len;
	sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (NULL == sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}

char	*ft_get_str(char **rest, char **line)
{
	char	*new_rest;
	size_t	i;

	i = 0;
	new_rest = NULL;
	while ((*(*rest + i) != '\n') && (*(*rest + i) != '\0'))
		i++;
	if (*(*rest + i) == '\n')
	{
		i++;
		*line = ft_substr(*rest, 0, i);
		new_rest = ft_strdup(*rest + i);
	}
	else
		*line = ft_strdup(*rest);
	free(*rest);
	*rest = NULL;
	return (new_rest);
}

ssize_t	ft_read_file(int fd, char **buffer, char **rest, char **line)
{
	char	*tmp;
	ssize_t	nbr;

	nbr = 1;
	while (!ft_strchr(*rest, '\n') && nbr)
	{
		nbr = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[nbr] = '\0';
		tmp = *rest;
		*rest = ft_strjoin(tmp, *buffer);
		free(tmp);
	}
	free(*buffer);
	*buffer = NULL;
	*rest = ft_get_str(rest, line);
	if (**line == '\0')
	{
		free(*line);
		*line = NULL;
	}
	return (nbr);
}

char	*get_next_line(int fd)
{
	static char	*rest[MAX_FD];
	char		*buffer;
	char		*line;
	ssize_t		num;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (read(fd, buffer, 0) < 0)
	{
		free(buffer);
		return (NULL);
	}
	if (!rest[fd])
		rest[fd] = ft_strdup("");
	num = ft_read_file(fd, &buffer, &rest[fd], &line);
	if (num == 0 && !line)
		return (NULL);
	return (line);
}
