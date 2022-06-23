/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:25:03 by kmorunov          #+#    #+#             */
/*   Updated: 2022/06/22 22:58:59 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_reset_sh(t_data *sh)
{
	free(sh->input);
	sh->input = NULL;
	if (sh->pp)
		free(sh->pp);
	sh->pp = NULL;
	ft_tokclear(&sh->tokens);
	sh->tokens = NULL;
	ft_restore_fds(sh);
	ft_cmdclear(&sh->cmd);
	sh->cmd = NULL;
	sh->pp_n = 0;
	sh->flag = 0;
	ft_restore_fds(sh);
}

void	ft_clean_sh(t_data *sh)
{
	ft_reset_sh(sh);
	rl_clear_history();
	free(sh->location);
	ft_clean_env(&sh->env);
	free(sh);
}

static void	ft_prep_sh(t_data *sh, char **envp)
{
	sh->pp = NULL;
	sh->env = NULL;
	sh->input = NULL;
	sh->tokens = NULL;
	sh->flag = 0;
	sh->pp_n = 0;
	sh->cmd = NULL;
	sh->status = 0;
	sh->location = NULL;
	if (ft_list_env(&sh->env, envp))
	{
		ft_clean_sh(sh);
		ft_putstr_fd("failed extract env\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_location(sh);
	sh->location = ft_getenv(sh, "_");
	ft_backup_fds(sh);
}

/*
static void	check(void)
{
	system("leaks minishell");
}
	atexit(check);
*/

static void	ft_loop(t_data *sh)
{
	while (1)
	{
		signal(SIGINT, ft_cntrl_cntrl);
		sh->input = readline("\033[1;35m<( ^.^ )>3.2$ \033[1;0m\033[0m");
		if (!sh->input)
		{
			ft_putstr_fd("\x1b[1A\x1b[13C exit\n", 1);
			break ;
		}
		if (ft_strlen(sh->input))
		{
			add_history(sh->input);
			if (!ft_lex(&sh))
			{
				ft_parse(&sh);
				ft_exec(sh);
			}
		}
		ft_reset_sh(sh);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*sh;

	(void)argc;
	(void )argv;
	sh = malloc(sizeof(t_data));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (!sh)
	{
		perror("system failure");
		exit(errno);
	}
	ft_prep_sh(sh, envp);
	ft_putstr_fd("\033[1;35mHello, I'm pleased to serve You.\033[1;0m\033[0m\n", 1);
	ft_loop(sh);
	ft_clean_sh(sh);
	return (0);
}
