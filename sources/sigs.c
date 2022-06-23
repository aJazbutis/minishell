/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 21:16:02 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/19 21:09:32 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cntrl_c(void)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 1);
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_cntrl_cntrl(int sig)
{
	if (sig == SIGINT)
		ft_cntrl_c();
}

void	ft_uncntrl(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

static void	ft_handle_cntrl_here(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	if (sig == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b", 1);
		ft_putchar_fd('\n', 1);
		exit(2);
	}
}

void	ft_cntrl_here(void)
{
	signal(SIGQUIT, ft_handle_cntrl_here);
	signal(SIGINT, ft_handle_cntrl_here);
}

/*void	ft_cntrl_backslash(void)
{
	struct termios *termios_p;
	
	if (tcgetattr(0, termios_p))
	{
		perror("???");
		return ;
	}
	if (tcsetattr(0, *c_lflag,*termios_p))
	{
		perror("???");
		return ;
	}
}*/
