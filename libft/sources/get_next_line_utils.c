/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:32:52 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/30 00:01:55 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strchr(char *s)
{
	if (s)
	{
		while (*s)
		{
			if (*s == '\n')
				return (s);
			else
				s++;
		}
	}
	return (NULL);
}

size_t	gnl_l(char *s)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (*(s + i))
			i++;
	}
	return (i);
}

char	*gnl_strdup(char *s)
{
	char	*sd;
	int		i;

	sd = NULL;
	if (s)
	{
		sd = (char *)malloc(gnl_l(s) + 1);
		if (!sd)
			return (NULL);
		i = -1;
		while (s[++i])
			sd[i] = s[i];
		sd[i] = s[i];
	}
	return (sd);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*das_s;
	int		i;
	int		j;

	if (!s1)
	{
		das_s = gnl_strdup(s2);
		return (das_s);
	}
	else if (!(*s2))
		return (s1);
	else
	{
		i = -1;
		das_s = (char *)malloc(gnl_l(s1) + gnl_l(s2) + 1);
		while (s1[++i])
			das_s[i] = s1[i];
		j = -1;
		while (s2[++j])
			das_s[i + j] = s2[j];
		das_s[i + j] = s2[j];
		free(s1);
	}
	return (das_s);
}

char	*gnl_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = (char *)malloc(len + 1);
	if (sub)
	{
		*(sub + len) = '\0';
		while (start < len)
		{
			len--;
			*(sub + len) = *(s + len);
		}
	}
	return (sub);
}
