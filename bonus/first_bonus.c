/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:46:49 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/06 16:55:28 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*cmd_finale;
	int		i;

	i = 0;
	if (!path || !cmd)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		cmd_finale = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_finale, 0) == 0)
			return (cmd_finale);
		free(cmd_finale);
		i++;
	}
	return (NULL);
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
		close(pipex->pipou[0][1]);
}

static void	child_exit(t_pipex *pipex)
{
	msg_error("First execve not working");
	close_all_pipe(pipex, 1);
	close_fd(pipex);
	free_all(pipex);
	exit(1);
}

void	first_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->fd_infile < 0)
	{
		free_parent(pipex);
		close_pipes(pipex);
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
	if (!pipex->cmd_args)
	{
		msg_error("Split first cmd args failed");
		free_parent(pipex);
		exit(1);
	}
	pipex->cmd = get_cmd(pipex->path_final, pipex->cmd_args[0]);
	if (!pipex->cmd)
		free_all_exit127(pipex, "Not finding first cmd", 0);
	execve(pipex->cmd, pipex->cmd_args, envp);
	child_exit(pipex);
}
