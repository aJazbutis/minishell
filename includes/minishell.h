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

//extern int	g_status;

typedef struct s_fd
{
	int			fd[3];
	int			st_fd[3];
	char		*in;
	char		*out;
	char		*err;
	char		**redir;
	int			append;
}t_fd;

typedef struct s_cmd
{
	char	**cmd;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_data
{
	t_env_lst	*env;
	char		*input;
	int			here_doc;
	int			pp1[4];
	int			*pp;
	int			pp_n;
	char		*limiter;
	t_cmd		*cmd;
	pid_t		id;
	int			status;
	int			append;
	int			fd[3];
	int			st_fd[3];
	char		*in;
	char		*out;
	char		*err;
}t_data;

void		ft_prompt(char *s);
void		ft_cd(t_data *sh, char **cmd);
void		ft_pwd(t_data *sh, char **cmd);
void		ft_exit(t_data *sh, char **cmd);
char		*ft_getenv(t_data *sh, char *s);
void		ft_unset(t_data *sh, char **cmd);
t_env_lst	*ft_get_env_var(t_data *sh, char *s);
char		**env_tab(t_data *sh, int x);
void		ft_env(t_data *sh);
void		ft_export(t_data *sh, char **cmd);
void		ft_add_env_var(t_data *sh, char **cmd);
int			ft_echo(t_data *sh, char **cmd);
int			ft_is_builtin(char *cmd);
void		ft_which_builtin(t_data *sh, char **cmd);
void		ft_exec(t_data *sh);
void		ft_exec_exe(t_data *sh, char **cmd);
void		ft_exec_cmd(t_data *sh, char **cmd);
void		ft_status(t_data *sh, char **cmd);
void		ft_underscore(t_data *sh, char **cmd);
void		ft_pathproofargs(/*t_data *sh,*/ char **cmd);

t_cmd		*ft_cmdnew(char **cmd);
int			ft_cmdsize(t_cmd *lst);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);
#endif
