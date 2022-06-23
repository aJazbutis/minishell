/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmorunov <kmorunov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 20:35:56 by ajazbuti          #+#    #+#             */
/*   Updated: 2022/06/22 22:52:43 by kmorunov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>

# include "libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/errno.h>
# include <sys/wait.h>
# include "envius.h"

# define TRUE 1
# define FALSE 0

typedef struct s_flst
{
	char			*str;
	int				nbr[2];
	struct s_flst	*next;
}	t_flst;

typedef struct s_cmd
{
	char			**cmd;
	t_flst			*in;
	t_flst			*out;
	t_flst			*heredoc;
	int				pp[2];
	int				here_fd;
	struct s_cmd	*next;
}	t_cmd;

enum e_tokens
{
	HASH=3,
	REDIR_FILE=4,
	REDIR_OUT=5,
	REDIR_APPEND=6,
	REDIR_IN=7,
	REDIR_HEREDOC=8,
	PIPE=9,
	WORD=10,
	OPERATOR=11
};

enum e_errors
{
	QT=1,
	PP=2,
	NL=3,
	DLM=4,
	INV=5,
	RD=6
};

typedef struct s_token
{
	int				type;
	char			*value;
	int				split;
	enum e_tokens	tok;
	enum e_errors	err;
	struct s_token	*next;
}	t_token;

typedef struct s_data
{
	t_env_lst	*env;
	char		*input;
	t_token		*tokens;
	int			flag;
	int			*pp;
	int			pp_n;
	t_cmd		*cmd;
	pid_t		id;
	int			status;
	int			fd[2];
	int			st_fd[3];
	char		*location;
}	t_data;

void		ft_mini_perror(t_data *sh, char *s);
int			ft_malloc_error(t_data *sh, void *s);

void		ft_clean_sh(t_data *sh);
char		*ft_getenv(t_data *sh, char *s);
t_env_lst	*ft_get_env_var(t_data *sh, char *s);
char		**env_tab(t_data *sh);
char		**env_tab_exp(t_data *sh);
void		ft_location(t_data *sh);

void		ft_cd(t_data *sh, char **cmd);
void		ft_pwd(t_data *sh, char **cmd);
void		ft_exit(t_data *sh, char **cmd);
void		ft_unset(t_data *sh, char **cmd);
void		ft_env(t_data *sh);
void		ft_export(t_data *sh, char **cmd);
void		ft_exp_print(t_data *sh);
void		ft_add_env_var(t_data *sh, char **cmd);
int			ft_echo(t_data *sh, char **cmd);
int			ft_status(t_data *sh);

int			ft_is_builtin(char *cmd);
void		ft_which_builtin(t_data *sh, char **cmd);
void		ft_exec(t_data *sh);
int			ft_pipes(t_data *sh);
void		ft_close_pipes(t_data *sh, int pp_fail);
void		ft_clean_child(t_data *sh, char *msg);
void		ft_pipeless(t_data *sh);
void		ft_pre_exec_env(t_data *sh, char *cmd);
void		ft_what_to_do(t_data *sh, char **cmd);
void		ft_exec_exe(t_data *sh, char **cmd);
void		ft_exec_cmd(t_data *sh, char **cmd);
void		ft_underscore(t_data *sh, char **cmd);
void		ft_pathproofargs(t_data *sh, char **cmd);
void		ft_minor_expnd(t_data*sh);

t_cmd		*ft_cmdnew(char **cmd, t_flst *in, t_flst *out, t_flst *here);
int			ft_cmdsize(t_cmd *lst);
void		ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void		ft_cmdclear(t_cmd **lst);

t_flst		*ft_flstnew(char *file, int append);
int			ft_flstsize(t_flst *lst);
void		ft_flstadd_back(t_flst **lst, t_flst *new);
void		ft_flstclear(t_flst **lst);

int			ft_here_doc(t_data *sh);
int			ft_here_pipes(t_data *sh);
void		ft_failed_pipes(t_data *sh, int i);
void		ft_close_pps(t_data *sh, int i);
void		ft_here_expand(t_data *sh, char *line, int fd);

void		ft_dup2_dup2(int inpt, int outpt);
int			ft_redir_out(t_data *sh, t_cmd *cmd, int out_fd);
int			ft_redir_in(t_data *sh, t_cmd *cmd, int in_fd);

int			ft_backup_fds(t_data *sh);
int			ft_restore_fds(t_data *sh);

void		ft_clean_sh(t_data *sh);

void		ft_uncntrl(void);
void		ft_cntrl_cntrl(int sig);
void		ft_cntrl_here(void);

int			ft_lex(t_data **data);
void		get_tokens(t_data **data);
void		check_comments(t_data **data);
void		do_expansion(t_data **data);
void		remove_quotes(t_data **data);
void		get_more_tokens(t_data **data);
void		delete_empty_tokens(t_data **data);

int			error_check(t_data **data);

int			token_count(t_token *token);
int			cut_token(char prev, char next, char *token, t_data *data);
t_token		*new_token(int c, char *token, t_data *data);
t_token		*last_token(t_token *head);
void		save_token(t_token **head, t_token *new_node);
void		ft_tokclear(t_token **token);

char		*ft_my_string_join(char *s1, char *s2);
char		*ft_my_substr(char *s, unsigned int start, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*append_str(char *string, int c);

int			is_space(int c);
int			is_delimeter(int c);
int			is_redir(int c);
void		*ft_realloc(void *ptr, size_t size);
void		check_flag(int c, t_data **data);
int			ft_strcmp(const char *s1, const char *s2);
int			pipe_count(t_token *token);
int			check_fn(const char *filename);

int			var_len(char *var);
int			get_position(char *s, int c);
char		*check_exp(t_data **data, t_token *head,
				char *dollar, int position);
char		*split_field(char *buffer);
void		put_dollar_back(t_data **data);

void		ft_parse(t_data **data);
t_flst		*new_redir(char *value, int redir_mode);
int			redirection(t_cmd **cmd, t_token *head);
void		cmd_init(t_cmd **cmd);
void		add_in(t_cmd **cmd, char *value, int redir_mode, int *count);
void		append_in(t_flst **head, t_flst *new_node);
void		add_out(t_cmd **cmd, char *value, int redir_mode);

#endif
