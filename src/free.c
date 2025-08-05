/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:56:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/03 16:52:53 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(t_pipex *pipex)
{
	free_parent(pipex);
	free_child(pipex);
}

void	free_all_exit127(t_pipex *pipex)
{
	free_all(pipex);
	exit(127);
}

void	free_parent_exit(t_pipex *pipex)
{
	free_parent(pipex);
	exit(1);
}

void	free_parent(t_pipex *pipex)
{
	int	i;

	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	if (pipex->path_final)
	{
		i = 0;
		while (pipex->path_final[i])
		{
			free(pipex->path_final[i]);
			i++;
		}
		free(pipex->path_final);
	}
}

void	free_child(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}
