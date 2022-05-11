/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:37:30 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/11 20:03:36 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static void	ft_cd_error_msg(char *s)
//{
static char	*ft_pwd_line(void)
{
	char	msg[256];
	char	*ret;

	ret = NULL;
	if (!getcwd(msg, sizeof(msg)))
	{
		perror("system malfunction");
//		g_status = errno;
	}
	else
	{
		ret = ft_strdup(msg);
		if (!ret)
			perror("system malfunction");
	}
	return (ret);
}

static void	ft_update_pwd(t_data *sh, char *old)
{
	t_env_lst	*node;

	node = ft_get_env_var(sh, "OLDPWD");
	if (node->unset)
	{
		if (old)
			free(old);
	}
	else
	{
		if (node->val)
			free(node->val);
		node->val = old;
	}
	node = ft_get_env_var(sh, "PWD");
	if (node->unset)
		return ;
	else
	{
		if (node->val)
			free(node->val);
		node->val = ft_pwd_line();
	}	
}

void	ft_cd(t_data *sh)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	if (!sh->cmd[1])
	{
		s =  ft_getenv(sh, "HOME");
		if (!s)
		{
			g_status = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
	}
//	else if (!ft_strncmp(".", sh->cmd[1], ft_strlen(sh->cmd[1])))
//		return ;
	else if (*sh->cmd[1] == '~')
	{
		sh->cmd[1]++;
		s = getenv("HOME"); 
		s = ft_strjoin(s, sh->cmd[1]);
		if (!s)
			perror("system malfunction");
		sh->cmd[1]--;
	}
	else
		s = ft_strdup(sh->cmd[1]);//malloc xheck
	tmp = ft_pwd_line();
	if (chdir(s))
	{
		free(tmp);
		tmp = ft_strjoin("minishell: cd: ", sh->cmd[1]);
		if (!tmp)
			perror("system malfunction");
		perror(tmp);
		free(tmp);
	}
	else
		ft_update_pwd(sh, tmp);
	free(s);
	g_status = errno;
}

void	ft_pwd(void)
{
	char msg[256];

	if (!getcwd(msg, sizeof(msg)))
	{
		perror("minishell: pwd:");
		g_status = errno;
	}
	else
	{
		ft_putstr_fd(msg, 1);
		write(1, "\n", 1);
	}
}
