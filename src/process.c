/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:59:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/10 15:54:12 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	second_dup_close(t_pipex *pipex)
{
	if (dup2(pipex->pipou[0], 0) < 0 || dup2(pipex->fd_outfile, 1) < 0)
	{
		close_fd_and_pipes(pipex);
		exit(1);
	}
	close_fd_and_pipes(pipex);
}

void	first_dup_close(t_pipex *pipex)
{
	if (dup2(pipex->pipou[1], 1) < 0 || dup2(pipex->fd_infile, 0))
	{	
		close_fd_and_pipes(pipex);
		exit(1);
	}
	close_fd_and_pipes(pipex);
}

void	first_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->fd_infile < 0)
	{
		close_fd_and_pipes(pipex);
		exit(1);
	}
	first_dup_close(pipex);
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args || !pipex->cmd_args[0])
		error_exit1(pipex, "Split first cmd failed");
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
		error_exit127(pipex, "Not finding first command");
	execve(pipex->cmd, pipex->cmd_args, envp);
	perror("Execve failed");
	free_all(pipex);
	exit(1);
}

void	second_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->fd_outfile < 0)
	{
		close_fd_and_pipes(pipex);
		free_all(pipex);
		exit(1);
	}
	second_dup_close(pipex);
	pipex->cmd_args = ft_split(av[3], ' ');
	if (!pipex->cmd_args)
		error_exit1(pipex, "Split second cmd failed");
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
		error_exit127(pipex, "Not finding second command");
	execve(pipex->cmd, pipex->cmd_args, envp);
	perror("Execve failed");
	free_all(pipex);
	exit(1);
}
