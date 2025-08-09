/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:01:04 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 15:55:32 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
