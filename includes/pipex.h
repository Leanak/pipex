/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:17:30 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/02 11:50:02 by lenakach         ###   ########.fr       */
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
int			msg_error(char *error);

// Free
void		free_parent(t_pipex *pipex);
void		free_child(t_pipex *pipex);
void		free_all(t_pipex *pipex);
void		free_parent_exit(t_pipex *pipex);
void		free_all_exit127(t_pipex *pipex);

// Process
void		second_child(t_pipex pipex, char **av, char **envp);
void		first_child(t_pipex pipex, char **av, char **envp);

// utils
void		forking(t_pipex *pipex, char **av, char **envp);
void		piping(t_pipex *pipex);
void		spliting(t_pipex *pipex);
void		close_fd(t_pipex *pipex);
void		close_fd_and_pipes(t_pipex *pipex);

#endif