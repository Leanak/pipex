/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:14:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 19:30:37 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

// write, read, fork, getpid, getppid, dup, dup2, pipe, execve, access, unlink
# include <unistd.h>
// open
# include <fcntl.h>
// perror
# include <stdio.h>
// exit, malloc, free
# include <stdlib.h>
// wait, waitpid
# include <sys/wait.h>
// strerror
# include <string.h>
// errno
# include "../libft/includes/libft.h"
# include <errno.h>

typedef struct s_pipex
{
	int		fd_infile;
	int		fd_outfile;
	int		pid[1024];
	int		pipou[1024][2];
	char	*path;
	char	**path_final;
	char	**cmd_args;
	char	*cmd;
	int		start;
	int		i;
	int		j;
}			t_pipex;

// Messages d'erreurs
int			msg(char *error);
void		msg_error(char *error);
void		error_exit1(t_pipex *pipex, char *error);
void		error_exitall(t_pipex *pipex, char *error, int count);
void		error_exit127(t_pipex *pipex, char *error, int count);
void		ultime_free_all(t_pipex *pipex, char *error, int count);
void		close_and_free_all(t_pipex *pipex, int count, char *error);
void		close_fd_and_exit(t_pipex *pipex);
void		close_parent(t_pipex *pipex, int i);

// Free
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);
void		free_all(t_pipex *pipex);
void		free_split(char **split);
void		free_all_exit127(t_pipex *pipex, const char *error, int count);

// Heredoc
void		handle_heredoc(char *limiter);

// Process
void		opening(t_pipex *pipex, char **av, int ac);
void		first_pipe(t_pipex *pipex, char **av, char **envp);
void		first_child(t_pipex *pipex, char **av, char **envp);
void		inter_pipe(t_pipex *pipex, char **av, int ac, char **envp);
void		last_pipe(t_pipex *pipex, char **av, int ac, char **envp);
void		last_child(t_pipex *pipex, char **av, int ac, char **envp);

// Close
void		close_fd(t_pipex *pipex);
void		close_all_pipe(t_pipex *pipex, int count);
void		close_pipes(t_pipex *pipex);

// Path & cmd
char		*find_path(char **envp);
char		*fill_path(char **path, char *cmd);
char		*get_cmd(char *cmd, char **envp);

#endif