/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:58:40 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/06 16:02:35 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	inter_pipe(t_pipex *pipex, char **av, int ac, char **envp)
{
	int	i;
	int	j;

	i = 1;
	if (pipex->start == 2)
		j = 3;
	else if (pipex->start == 3)
		j = 4;
	while (i < ac - 4)
	{
		if (pipe(pipex->pipou[i]) < 0)
		{
			msg_error("pipe I not working");
			close_fd(pipex);
			exit(1);
		}
		pipex->pid[i] = fork();
		if (pipex->pid[i] == 0)
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
			pipex->cmd_args = ft_split(av[j], ' ');
			if (!pipex->cmd_args)
			{
				msg_error("Split cmd args failed");
				close_all_pipe(pipex, i);
				close_fd(pipex);
				free_parent(pipex);
				exit(1);
			}
			pipex->cmd = get_cmd(pipex->path_final, pipex->cmd_args[0]);
			if (!pipex->cmd)
			{
				perror("Not finding cmd i");
				free_all(pipex);
				close_all_pipe(pipex, i);
				close_fd(pipex);
				exit(127);
			}
			execve(pipex->cmd, pipex->cmd_args, envp);
			msg_error("HOLA Execve not working");
			free_all(pipex);
			exit(1);
		}
		else if (pipex->pid[i] < 0)
		{	
			close(pipex->pipou[i][0]);
			close(pipex->pid[i - 1][0]);
			msg_error("INTER FORK FAILED");
			exit (1);
		}	
		else
		{
			close(pipex->pipou[i - 1][0]);
			close(pipex->pipou[i][1]);
		}
		i++;
		j++;
	}
}
