/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:46:49 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 18:12:36 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_pipex(t_pipex *pipex)
{
	pipex->path = NULL;
	pipex->path_final = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd = NULL;
}

void	first_pipe(t_pipex *pipex, char **av, char **envp)
{
	if (pipe(pipex->pipou[0]) < 0)
	{
		msg_error("Error with first pipe");
		close_fd(pipex);
		exit(1);
	}
	pipex->pid[0] = fork();
	if (pipex->pid[0] == 0)
		first_child(pipex, av, envp);
	else if (pipex->pid[0] < 0)
	{
		close(pipex->pipou[0][1]);
		msg_error("FIRST FORK FAILED");
		exit(1);
	}
	else
	{
		close(pipex->pipou[0][1]);
		close(pipex->pipou[0][0]);
	}
}

static void	child_exit(t_pipex *pipex, char *error)
{
	perror(error);
	close_all_pipe(pipex, 1);
	close_fd(pipex);
	free_all(pipex);
	exit(1);
}

void	first_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->fd_infile < 0)
	{
		close_pipes(pipex);
		close_fd(pipex);
		exit(1);
	}
	dup2(pipex->pipou[0][1], 1);
	dup2(pipex->fd_infile, 0);
	close(pipex->pipou[0][1]);
	close(pipex->pipou[0][0]);
	close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	pipex->cmd_args = ft_split(av[pipex->start], ' ');
	if (!pipex->cmd_args || !pipex->cmd_args[0])
		error_exit1(pipex, "SPlit first cmd failed");
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
		error_exit127(pipex, "Not finding first cmd", 0);
	execve(pipex->cmd, pipex->cmd_args, envp);
	child_exit(pipex, "Execve not working");
}
