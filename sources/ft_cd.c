/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 17:37:30 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/21 21:23:04 by ajazbuti         ###   ########.fr       */
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
		perror("system malfunction");
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

void	ft_cd(t_data *sh, char **cmd)
{
	char	*tmp;
	char	*s;

	tmp = NULL;
	s = NULL;
	ft_underscore(sh, cmd);
	if (!cmd[1])
	{
		s =  ft_getenv(sh, "HOME");
		if (!s)
		{
			sh->status = 1;
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	//		return ;
		}
	}
	else if (*cmd[1] == '~')
	{
		cmd[1]++;
		s = getenv("HOME"); 
		s = ft_strjoin(s, cmd[1]);
		if (!s)
			perror("system malfunction");
		cmd[1]--;
	}
	else
	{
		s = ft_strdup(cmd[1]);//malloc xheck
		if (!s)
			perror("system malfunction");
	}
	if (!s)
		return ;
	tmp = ft_pwd_line();
	if (chdir(s))
	{
		free(tmp);
		tmp = ft_strjoin("minishell: cd: ", cmd[1]);
		if (tmp)
			perror("system malfunction");
		else
			perror(tmp);
		free(tmp);
	}
	else
		ft_update_pwd(sh, tmp);
	free(s);
}

void	ft_pwd(t_data *sh, char **cmd)
{
	char		msg[256];
	if (!sh)
		return ;
	t_env_lst	*tmp;
	int			i;

	tmp = ft_get_env_var(sh, "_");
	if (!tmp->unset)
	{
		if (tmp->val)
			free(tmp->val);
		i = 0;
		while (cmd[i + 1])
			i++;
		tmp->val = ft_strdup(cmd[i]);
		if (!tmp->val)
			perror("system malfunction");
	}
//	ft_underscore(sh);
	if (!getcwd(msg, sizeof(msg)))
	{
		perror("minishell: pwd:");
		sh->status = errno;
	}
	else
	{
		ft_putstr_fd(msg, 1);
		write(1, "\n", 1);
	}
}
