/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornhol <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:57:51 by scornhol          #+#    #+#             */
/*   Updated: 2021/11/04 14:57:59 by scornhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* man strchr. The strchr() function locates the first occurrence of c in
 * the string pointed to by s.
 *
 * man strlen. The strlen() function computes the length of the string s.
 *
 * man strlcpy. Size-bounded string copying.
 *
 * man strlcat. Size-bounded string concatenation.
 *
 * man strdup. strdup - save a copy of a string. The strdup() function
 * allocates sufficient memory for a copy of the string s1, does the copy,
 * and returns a pointer to it.
 *
 * ft_strjoin. Allocates (with malloc(3)) and returns a new string, which is
 * the result of the concatenation of ’s1’ and ’s2’.
 *
 * ft_substr. Allocates (with malloc(3)) and returns a substring from the
 * string ’s’. The substring begins at index ’start’ and is of maximum size
 * ’len’.																	  */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	l;

	l = ft_strlen(src);
	i = 0;
	if (!dstsize)
		return (l);
	while (*dst && dstsize)
	{
		dst++;
		i++;
		dstsize--;
	}
	while (*src && dstsize > 1)
	{
		*dst++ = *src++;
		dstsize--;
	}
	if (dstsize != 0)
		*dst = '\0';
	return (l + i);
}

char	*ft_strdup(const char *s1)
{
	char	*str_cpy;
	size_t	i;

	i = ft_strlen(s1) + 1;
	str_cpy = (char *)malloc(sizeof(char) * i);
	if (NULL == str_cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_cpy[i] = s1[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}
