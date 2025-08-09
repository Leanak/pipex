/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:11:31 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 18:01:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	last_pipe(t_pipex *pipex, char **av, int ac, char **envp)
{
	pipex->pid[ac - 3] = fork();
	if (pipex->pid[ac - 3] == 0)
		last_child(pipex, av, ac, envp);
	else if (pipex->pid[ac - 3] < 0)
	{	
		close(pipex->pipou[ac - 3][0]);
		msg_error("LAST FORK FAILED");
		exit (1);
	}	
	else
		close(pipex->pipou[ac - 5][0]);
}

void	last_child(t_pipex *pipex, char **av, int ac, char **envp)
{
	if (pipex->fd_outfile < 0)
	{
		//free_parent(pipex);
		close_fd(pipex);
		exit(1);
	}
	dup2(pipex->pipou[ac - 5][0], 0);
	dup2(pipex->fd_outfile, 1);
	close(pipex->pipou[ac - 5][0]);
	close(pipex->pipou[ac - 5][1]);
	close(pipex->fd_outfile);
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	pipex->cmd_args = ft_split(av[ac - 2], ' ');
	if (!pipex->cmd_args)
	{
		msg_error("Split cmd args failed");
		//free_parent(pipex);
		exit(1);
	}
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
	{
		msg_error("Not finding command with access");
		free_all(pipex);
		exit(127);
	}
	execve(pipex->cmd, pipex->cmd_args, envp);
	msg_error(" HEY Execve not working");
	free_all(pipex);
	exit(1);
}