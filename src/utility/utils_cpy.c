/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snpark <snpark@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:13:28 by snpark            #+#    #+#             */
/*   Updated: 2021/12/22 17:31:12 by snpark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char
	*ft_strcat(char *s1, const char *s2)
{
	char	*ptr;

	if (!s2 || !*s2)
		return (s1);
	ptr = s1;
	while (*s1)
		++s1;
	while (*s2)
		*s1++ = *s2++;
	if (*s2 == '\0')
		*s1 = *s2;
	return (ptr);
}

char
	*ft_strcpy(char *dst, const char *src)
{
	char	*ptr;

	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = *src;
	return (dst);
}

char
	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (dst == NULL)
		return (NULL);
	i = -1;
	while (++i < len && src[i])
		dst[i] = src[i];
	while (i < len)
		dst[i++] = '\0';
	return (dst);
}

void
	ft_strmove(char *dest, char *src, int len)
{
	if (len < 0)
		return ;
	while (len--)
		*dest++ = *src++;
	*dest = *src;
}
