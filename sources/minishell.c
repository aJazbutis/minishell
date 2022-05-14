/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:21:54 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/14 20:16:09 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

/*static void ft_clean_sh(t_data *sh, char *sh->input)	
{
	free(sh->input);
	sh->here_doc = 0;
	sh->limiter = NULL;
	sh->append = 0;
	sh->out = NULL;
	ft_free_tab(sh->cmd);
	sh->cmd = NULL;
}*/
static void ft_reset_sh(t_data *sh)	
{
	free(sh->input);
	sh->input = NULL;
	sh->here_doc = 0;
	sh->limiter = NULL;
	sh->append = 0;
	sh->out = NULL;
	ft_free_tab(sh->cmd);
	sh->cmd = NULL;
}

int	main(void)
{
//	int		i;
//	char	**s;
//	char	**s1;
//	t_env_lst *env;
//	t_env_lst *tmp;
	t_data	*sh;

	printf("ECHO NEEDS FIXXING\n");

	g_status = 0;
//	while (g_status++ < 128)
//		printf("%s\n", strerror(g_status));
//	s = NULL;
//	s1 = NULL;
	sh = malloc(sizeof(t_data));
//	sh->env = NULL;
	ft_memset(sh, 0, sizeof(sh));
	ft_list_env(&sh->env);
//	tmp = sh->env;
//	while (tmp)
//	{
//		printf("%s\n", tmp->var);
//		printf("%s\n", tmp->val);
//		tmp = tmp->next;
//	}
	while (1)
	{
		sh->input = readline("minishell-0.0$ ");
		if (!sh->input)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (ft_strlen(sh->input))
		{
			add_history(sh->input);
		sh->cmd = ft_split(sh->input, ' ');
//		sh->cmd = s;
//		printf("%s\n", sh->input);
//		printf("%p\n", sh->cmd);
//tmp = sh->env;
//	while (tmp)
//	{
//		printf("%s\n", tmp->var);
//		printf("%s\n", tmp->val);
//		tmp = tmp->next;
//	}
		if (!ft_is_builtin(sh))
		{
			printf("work more\n");
			if (*sh->cmd[0] == '.' || *sh->cmd[0] == '~')
				ft_execute_executable(sh);
			else
				ft_execute_command(sh);
		}

/*		if (s && !ft_strncmp(s[0], "exit", 5))
		{
			free(sh->input);
			ft_exit(sh);
		}
	if (ft_strchr(s[0], '='))
			ft_add_env_var(sh);

		if (!ft_strncmp(s[0], "cd", 3))
			ft_cd(sh, ft_strdup(s[1]));
		if (!ft_strncmp(sh->input, "pwd", 4))
			ft_pwd();
		if (!ft_strncmp(s[0], "unset", 6))
			ft_unset(sh, s[1]);
		if (!ft_strncmp(s[0], "env", 4))
			ft_env(sh);
		if (!ft_strncmp(sh->cmd[0], "echo", 5))
			ft_echo(sh);*/
	//	if (!ft_strncmp(sh->cmd[0], "export", 7))
	//		ft_export(sh);

	//		ft_free_tab(s);
//		free(sh->input);
		}
		ft_reset_sh(sh);
	}
//	if (sh->input)
		rl_clear_history();
//	tmp = sh->env;
//	while (tmp)
//	{
//		printf("%s\n", tmp->var);
//		printf("%s\n", tmp->val);
//		tmp = tmp->next;
//	}
//	s = env_tab(sh);
//	i = -1;
//	while (s[++i])
//		printf("%s\n", s[i]);
//	ft_free_tab(s);
//printf("???\n");
	ft_clean_env(&sh->env);
	free(sh);
	system("leaks minishell");
	return (0);
}
