/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_exp_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:12:33 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 23:00:59 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_len(char *var)
{
	int	i;

	i = 0;
	if (var[i] == '?')
		return (TRUE);
	if (var[i] != '_' && !ft_isalpha(var[i]))
		return (FALSE);
	while (var[i] == '_' || ft_isalnum(var[i]))
		i++;
	return (i);
}

int	get_position(char *s, int c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	len = ft_strlen(s);
	if (s == NULL)
		return (-1);
	while (i <= len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*split_field(char *buffer)
{
	char	*str;
	int		i;

	str = NULL;
	i = 0;
	while (buffer[i])
	{
		if (!is_space(buffer[i]))
		{
			str = append_str(str, buffer[i]);
			if (is_space(buffer[i + 1]))
				str = append_str(str, ' ');
		}
		i++;
	}
	free(buffer);
	return (str);
}

char	*check_exp(t_data **data, t_token *head, char *dollar, int position)
{
	char	*before;
	char	*after;
	char	*buff;
	char	*buff2;
	int		l;

	l = var_len(dollar + 1);
	dollar = ft_substr(dollar, 1, l);
	if (dollar[0] == '?')
		buff = ft_itoa((*data)->status);
	else
		buff = ft_getenv((*data), dollar);
	free(dollar);
	dollar = NULL;
	if (buff && head->split != 0)
		buff = split_field(buff);
	before = ft_my_substr(head->value, 0, position);
	after = ft_my_substr(head->value, position + l + 1, ft_strlen(head->value));
	buff2 = ft_my_string_join(before, buff);
	free(buff);
	free(before);
	dollar = ft_my_string_join(buff2, after);
	free(after);
	free(buff2);
	return (dollar);
}
