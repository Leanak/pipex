/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:58:40 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/10 17:40:23 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	dup_and_close(t_pipex *pipex, int i)
{
	dup2(pipex->pipou[i][1], 1);
	dup2(pipex->pipou[i - 1][0], 0);
	close(pipex->pipou[i][1]);
	close(pipex->pipou[i][0]);
	close(pipex->pipou[i - 1][0]);
	close(pipex->pipou[i - 1][1]);
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
}

static void	inter_args(t_pipex *pipex, int *j, int i, char **av)
{
	pipex->cmd_args = ft_split(av[++(*j)], ' ');
	if (!pipex->cmd_args)
	{
		perror("OK");
		get_next_line(-1);
		close_and_free_all(pipex, i, "");
	}
}

static void	inter_cmd(t_pipex *pipex, char **envp, int i)
{
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
		error_exit127(pipex, "Not finding cmd i", i);
}

static void	fork_error(t_pipex *pipex, int i)
{
	close(pipex->pipou[i][0]);
	close(pipex->pipou[i - 1][0]);
	perror("Inter fork failed");
	exit(1);
}

void	inter_pipe(t_pipex *pipex, char **av, int ac, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 3;
	if (pipex->start == 2)
		j = 2;
	while (++i < ac - 4)
	{
		if (pipe(pipex->pipou[i]) < 0)
			close_fd_and_exit(pipex);
		pipex->pid[i] = fork();
		if (pipex->pid[i] == 0)
		{
			dup_and_close(pipex, i);
			inter_args(pipex, &j, i, av);
			inter_cmd(pipex, envp, i);
			execve(pipex->cmd, pipex->cmd_args, envp);
			close_and_free_all(pipex, i, "Execve not working");
		}
		else if (pipex->pid[i] < 0)
			fork_error(pipex, i);
		else
			close_parent(pipex, i);
	}
}
