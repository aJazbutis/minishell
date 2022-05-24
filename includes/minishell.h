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
# include <fcntl.h>
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

typedef struct s_flst
{
	char			*file;
	int				append;
	struct s_flst	*next;
}t_flst;

typedef struct s_cmd
{
	char	**cmd;
	t_flst	*in;
	t_flst	*out;
	struct s_cmd	*next;
}t_cmd;

typedef struct s_data
{
	t_env_lst	*env;
	char		*input;
	int			here_doc;
	char		*limiter;
	int			pp1[4];
	int			*pp;
	int			pp_n;
	t_cmd		*cmd;
	pid_t		id;
	int			status;
	int			append;
	int			fd[3];
	int			st_fd[3];
	char		*in;
	char		*out;
	char		*err;
	char		*location;
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

t_cmd		*ft_cmdnew(char **cmd, t_flst *in, t_flst *out);
int			ft_cmdsize(t_cmd *lst);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);

t_flst		*ft_flstnew(char *file, int append);
int			ft_flstsize(t_flst *lst);
void		ft_flstadd_back(t_flst **lst, t_flst *new);
void		ft_flstclear(t_flst **lst);

int			ft_redir_out(t_flst *out);
int			ft_redir_in(t_flst *in);
#endif
