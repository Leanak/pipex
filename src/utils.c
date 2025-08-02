/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 11:45:11 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/02 11:49:54 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	forking(t_pipex *pipex, char **av, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		first_child(*pipex, av, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		second_child(*pipex, av, envp);
}

void	piping(t_pipex *pipex)
{
	if (pipe(pipex->pipou) < 0)
	{
		msg_error("Error with the pipe");
		close_fd(pipex);
	}
}

void	spliting(t_pipex *pipex)
{
	if (!pipex->path_final)
	{
		msg_error("Split path failed\n");
		close_fd_and_pipes(pipex);
		exit(1);
	}
}
