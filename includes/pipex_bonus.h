/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:14:20 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/06 16:55:46 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
}			t_pipex;

// Messages d'erreurs
int			msg(char *error);
int			msg_error(char *error);

// Free
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);
void		free_all(t_pipex *pipex);
void		free_split(char **split);
void		free_all_exit127(t_pipex *pipex, const char *error, int count);

// Heredoc
void		handle_heredoc(char *limiter);

void		first_pipe(t_pipex *pipex, char **av, char **envp);
void		first_child(t_pipex *pipex, char **av, char **envp);
void		inter_pipe(t_pipex *pipex, char **av, int ac, char **envp);
void		last_pipe(t_pipex *pipex, char **av, int ac, char **envp);
void		last_child(t_pipex *pipex, char **av, int ac, char **envp);
char		*get_cmd(char **path, char *cmd);

// close
void		close_fd(t_pipex *pipex);
void		close_all_pipe(t_pipex *pipex, int count);
void		close_pipes(t_pipex *pipex);

#endif