/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:01:04 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/10 17:41:12 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	close_fd_and_exit(t_pipex *pipex)
{
	close_fd(pipex);
	exit(1);
}

void	close_and_free_all(t_pipex *pipex, int count, char *error)
{
	if (error)
		perror(error);
	if (pipex->cmd)
		free(pipex->cmd);
	close_all_pipe(pipex, count);
	get_next_line(-1);
	close_fd(pipex);
	free_all(pipex);
	exit (1);
}

void	close_fd(t_pipex *pipex)
{
	if (pipex->fd_infile && pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile && pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
}

void	close_all_pipe(t_pipex *pipex, int count)
{
	int	i;

	i = 0;
	if (pipex->pipou[0])
	{
		while (i < count)
		{
			close(pipex->pipou[i][0]);
			close(pipex->pipou[i][1]);
			i++;
		}
	}
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipou[0][1]);
	close(pipex->pipou[0][0]);
}
