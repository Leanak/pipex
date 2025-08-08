/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:17:30 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/08 15:32:38 by lenakach         ###   ########.fr       */
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
	int		pid1;
	int		pid2;
	int		pipou[2];
	char	*path;
	char	**path_final;
	char	**cmd_args;
	char	*cmd;
}			t_pipex;

// Messages d'erreurs
int			msg(char *error);
void		error_exit1(t_pipex *pipex, char *error);
void		error_exit127(t_pipex *pipex, char *error);

// Free
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);
void		free_all(t_pipex *pipex);
void		free_split(char **split);
void		init_pipex(t_pipex *pipex);

// Process
void		second_child(t_pipex *pipex, char **av, char **envp);
void		first_child(t_pipex *pipex, char **av, char **envp);

// utils
void		opening(t_pipex *pipex, char **av, int ac);
void		forking(t_pipex *pipex, char **av, char **envp);
void		piping(t_pipex *pipex);
char		*find_path(char **envp);
char		*get_cmd(char *cmd, char **envp);

// Close
void		close_pipes(t_pipex *pipex);
void		close_fd(t_pipex *pipex);
void		close_fd_and_pipes(t_pipex *pipex);

#endif