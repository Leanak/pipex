/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 13:10:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/02 13:19:55 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"


/* void	close_pipes(t_pipex pipex, int i)
{
	close(pipex.pipou[i][0]);
	close(pipex.pipou[i][1]);
} */

void	close_fd(t_pipex *pipex)
{
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	exit(1);
}

void	close_fd_and_pipes(t_pipex *pipex)
{
	close_fd(pipex);
	//close_pipes(*pipex);
}