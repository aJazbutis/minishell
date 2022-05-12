/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajazbuti <ajazbuti@student.42heilbronn.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:01:33 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/04/21 18:23:13 by ajazbuti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/errno.h>
# include "libft.h"
# include "lexius.h"
# include "envius.h"

extern int	g_status;

typedef struct s_data
{
	t_env_lst	*env;
	char		*input;
	int			here_doc;
	int			pp1[2];
	char		*limiter;
	char		*out;
	int			append;
	char		**cmd;
}t_data;

void	ft_prompt(char *s);
void	ft_cd(t_data *sh);
void	ft_pwd(t_data *sh);
void	ft_exit(t_data *sh);
char	*ft_getenv(t_data *sh, char *s);
void	ft_unset(t_data *sh);
t_env_lst *ft_get_env_var(t_data *sh, char *s);
char	**env_tab(t_data *sh);
void	ft_env(t_data *sh);
void	ft_export(t_data *sh);
void	ft_add_env_var(t_data *sh);
int		ft_echo(t_data *sh);
void	ft_execute_executable(t_data *sh, char *path, char **args);
int		ft_is_builtin(t_data *sh);
void	ft_execute_command(t_data *sh);
void	ft_status(int status);
void	ft_underscore(t_data *sh);
#endif
