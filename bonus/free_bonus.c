/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:51:12 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 15:41:27 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

	if (pipex->cmd_args)
	{
		i = 0;
		while (pipex->cmd_args[i])
		{
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
}

void	free_all(t_pipex *pipex)
{
	free_parent(pipex);
	free_child(pipex);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_all_exit127(t_pipex *pipex, const char *error, int count)
{
	perror(error);
	free_all(pipex);
	close_all_pipe(pipex, count);
	close_fd(pipex);
	get_next_line(-1);
	exit(127);
}
