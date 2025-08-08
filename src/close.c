/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:33:26 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/08 15:28:44 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	close_pipes(t_pipex *pipex)
{
	if (pipex->pipou[0] > 0)
		close(pipex->pipou[0]);
	if (pipex->pipou[1] > 0)
		close(pipex->pipou[1]);
}

void	close_fd_and_pipes(t_pipex *pipex)
{
	close_fd(pipex);
	close_pipes(pipex);
}

void	close_fd(t_pipex *pipex)
{
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
}
