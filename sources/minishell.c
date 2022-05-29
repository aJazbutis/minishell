/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:21:54 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/05/30 00:23:16 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	g_status;

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
//	int i;

//	i = -1;
	free(sh->input);
	sh->input = NULL;
	if (sh->pp)
		free(sh->pp);
	sh->pp = NULL;

	ft_cmdclear(&sh->cmd);
	sh->cmd = NULL;
	ft_hereclear(&sh->heredoc);
	sh->heredoc = NULL;
//	sh->append = 0;
//	free(sh->out);
//	sh->out = NULL;
//	while (sh->cmd[++i])
//		ft_free_tab(sh->cmd[i]);
//	free(sh->cmd);
}


//int	main(void)
int	main(int argc, char	**argv)

{
	int		i = 0;
	char	*s1;
//	t_env_lst *env;
//	t_env_lst *tmp;
	t_data	*sh;
	t_flst	*in;
	t_flst	*out;
	t_here	*here;

	if (!argc)
		exit(1);
	s1 = NULL;
	in = NULL;
	out = NULL;
	here = NULL;
	sh = malloc(sizeof(t_data));
	ft_memset(sh, 0, sizeof(sh));
	ft_list_env(&sh->env);

/*	while (argv[++i])
	{
		if (i % 2)
			ft_flstadd_back(&in, ft_flstnew(ft_strdup(argv[i]), 0));
		else
			ft_flstadd_back(&out, ft_flstnew(ft_strdup(argv[i]), 0));
	}*/
	while (argv[++i])
		ft_hereadd_back(&here, ft_herenew(ft_strdup(argv[i])));

			sh->heredoc = here;
	sh->st_fd[0] = dup(0);
	sh->st_fd[1] = dup(1);
	sh->st_fd[2] = dup(2);
	s1 = ft_getenv(sh, "_");
	sh->location = ft_strjoin(s1, "-ft_env");
	free(s1);

/*	while (argv[++i])
	{
		printf("%s\n", argv[i]);
		if (!ft_strncmp("|", argv[i], ft_strlen(argv[i])))
			sh->pp_nbr++;
		else
		{
			tmp = ft_cmdnew(ft_split(argv[i], ' '));
			ft_cmdadd_back(&sh->cmd, tmp);
		}
	}
	tmp = sh->cmd;
	while (tmp)
	{
		i = -1;
		while (tmp->cmd[++i])
		{
		   printf("%s\n",tmp->cmd[i]);	
		}
		
		   tmp = tmp->next;
	}
	printf("%d\n", sh->pp_nbr);
	ft_e
*/
//	ft_get_cmds(argv, sh);
	//printf("ECHO NEEDS FIXXING\n");
	char	**s;

//	t_cmd	*tmp;
	while (1)
	{

	i = -1;
		sh->input = readline("minishell-1.0$ ");
		if (!sh->input)
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		if (ft_strlen(sh->input))
		{
			add_history(sh->input);
			s = ft_split(sh->input, '|');
			while (s[++i])
			{
				if (!i)
					ft_cmdadd_back(&sh->cmd, ft_cmdnew(ft_split(s[i], ' '), in, NULL));
				else if (s[i + 1] == NULL)
					ft_cmdadd_back(&sh->cmd, ft_cmdnew(ft_split(s[i], ' '), NULL, out));
				else
					ft_cmdadd_back(&sh->cmd, ft_cmdnew(ft_split(s[i], ' '), NULL, NULL));	
			}
			ft_free_tab(s);
			sh->pp_n = ft_cmdsize(sh->cmd) - 1;
			if (sh->heredoc)
				ft_here_doc(sh);
/*	tmp = sh->cmd;
	while (tmp)
	{
		i = -1;
//		while (tmp->cmd[++i])
		   printf("%s\n",tmp->cmd[++i]);	
		tmp = tmp->next;
	}*/
//	printf("%d\n", sh->pp_n);

			ft_exec(sh);
		}
		ft_reset_sh(sh);
		in = NULL;
		out = NULL;
	}
	rl_clear_history();
ft_reset_sh(sh);
free(sh->location);

	ft_clean_env(&sh->env);
	free(sh);
	i = -1;
	while (++i < 3)
		close(sh->st_fd[i]);
	system("leaks minishell");
	return (0);
}
