/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_string_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:51:38 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 22:09:12 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_my_string_join(char *s1, char *s2)
{
	char	*s;
	size_t	l1;
	size_t	l2;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s = NULL;
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	s = (char *)ft_calloc(l1 + l2 + 1, sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, s1, l1 + 1);
	ft_strlcat(s, s2, l1 + l2 + 1);
	return (s);
}

char	*ft_my_substr(char *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	size;

	if (!s)
		return (NULL);
	sub_str = NULL;
	size = ft_strlen(s + start);
	if (len == 0)
		return (NULL);
	if (size < len)
		sub_str = (char *)ft_calloc(sizeof(char), (size + 1));
	else
		sub_str = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!sub_str)
		return (sub_str);
	if (start > ft_strlen(s))
		return (sub_str);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	j = len;
	if (s2 != NULL)
	{
		while (s2[i] != '\0')
		{
			s1[j] = s2[i];
			j++;
			i++;
		}
		s1[j] = '\0';
	}
	return (s1);
}

char	*append_str(char *string, int c)
{
	char	*str;
	char	*temp;
	int		len;

	str = NULL;
	if (c == '\0')
		return (string);
	str = ft_calloc(2, sizeof(char));
	if (str == NULL)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	len = ft_strlen(string);
	temp = (char *)ft_calloc((len + 2), sizeof(char));
	if (string)
		ft_memcpy(temp, string, len + 1);
	ft_strcat(temp, str);
	free(str);
	if (string)
		free(string);
	return (temp);
}
