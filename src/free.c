/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:56:16 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/10 16:16:38 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	free_all(t_pipex *pipex)
{
	if (!pipex)
		return ;
	if (pipex->cmd)
		free(pipex->cmd);
	free_parent(pipex);
	free_child(pipex);
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
	if (pipex->cmd_args)
	{
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
	}
	free(pipex->cmd_args);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}
