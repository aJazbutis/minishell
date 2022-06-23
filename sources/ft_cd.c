/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:37:30 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/23 14:18:55 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_pwd_line(t_data *sh)
{
	char	msg[256];
	char	*ret;

	ret = NULL;
	if (!getcwd(msg, sizeof(msg)))
	{
		perror("system malfunction");
		sh->status = errno;
	}
	else
	{
		ret = ft_strdup(msg);
		ft_malloc_error(sh, ret);
	}
	return (ret);
}

static void	ft_update_pwd(t_data *sh, char *old)
{
	t_env_lst	*node;

	node = ft_get_env_var(sh, "OLDPWD");
	node->unset = 0;
	if (node->val)
		free(node->val);
	node->val = old;
	node = ft_get_env_var(sh, "PWD");
	node->unset = 0;
	if (node->val)
		free(node->val);
	node->val = ft_pwd_line(sh);
}

static void	ft_home_not_set(void)
{
	ft_putstr_fd("\033[1;35m<( ^.^ )>\033[1;0m\033[0m", 2);
	ft_putstr_fd(": cd: HOME not set\n", 2);
}

static char	*ft_where_to(t_data *sh, char **cmd)
{
	char	*s;

	if (!cmd[1])
	{
		s = ft_getenv(sh, "HOME");
		if (!s)
		{
			sh->status = 1;
			ft_home_not_set();
		}
	}
	else if (*cmd[1] == '~')
	{
		cmd[1]++;
		s = getenv("HOME");
		s = ft_strjoin(s, cmd[1]);
		ft_malloc_error(sh, s);
		cmd[1]--;
	}
	else
	{
		s = ft_strdup(cmd[1]);
		ft_malloc_error(sh, s);
	}
	return (s);
}

void	ft_cd(t_data *sh, char **cmd)
{
	char	*tmp;
	char	*s;

	sh->status = 0;
	tmp = NULL;
	s = NULL;
	ft_underscore(sh, cmd);
	s = ft_where_to(sh, cmd);
	if (!s)
		return ;
	tmp = ft_pwd_line(sh);
	if (chdir(s))
	{
		free(tmp);
		tmp = ft_strjoin("\033[1;35m<( ^.^ )>\033[1;0m\033[0m: cd: ", cmd[1]);
		if (!tmp)
			ft_malloc_error(sh, tmp);
		else
			perror(tmp);
		free(tmp);
		sh->status = 1;
	}
	else
		ft_update_pwd(sh, tmp);
	free(s);
}
