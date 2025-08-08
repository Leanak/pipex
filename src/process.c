/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:59:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/08 15:33:25 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->fd_infile < 0)
	{
		close_fd_and_pipes(pipex);
		exit(1);
	}
	dup2(pipex->pipou[1], 1);
	dup2(pipex->fd_infile, 0);
	close(pipex->pipou[0]);
	close(pipex->pipou[1]);
	close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args || !pipex->cmd_args[0])
		error_exit1(pipex, "Split cmd args failed");
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
		error_exit127(pipex, "Not finding command with access");
	execve(pipex->cmd, pipex->cmd_args, envp);
	perror("Execve not working");
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
	dup2(pipex->pipou[0], 0);
	dup2(pipex->fd_outfile, 1);
	close(pipex->pipou[1]);
	close(pipex->pipou[0]);
	close(pipex->fd_outfile);
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	pipex->cmd_args = ft_split(av[3], ' ');
	if (!pipex->cmd_args || !pipex->cmd_args[0])
		error_exit1(pipex, "Split cmd args failed");
	pipex->cmd = get_cmd(pipex->cmd_args[0], envp);
	if (!pipex->cmd)
		error_exit127(pipex, "Not finding command with access");
	execve(pipex->cmd, pipex->cmd_args, envp);
	perror("Execve not working");
	free_all(pipex);
	exit(1);
}
