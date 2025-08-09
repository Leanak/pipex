/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:46:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 19:46:18 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

void	error_exit1(t_pipex *pipex, char *error)
{
	perror(error);
	free_child(pipex);
	get_next_line(-1);
	exit(1);
}

void	error_exitall(t_pipex *pipex, char *error, int count)
{
	perror(error);
	free_all(pipex);
	close_all_pipe(pipex, count);
	close_fd(pipex);
	get_next_line(-1);
	exit(1);
}

void	error_exit127(t_pipex *pipex, char *error, int count)
{
	perror(error);
	free_all(pipex);
	close_all_pipe(pipex, count);
	close_fd(pipex);
	get_next_line(-1);
	exit(127);
}

void	close_parent(t_pipex *pipex, int i)
{
	close(pipex->pipou[i - 1][0]);
	close(pipex->pipou[i][1]);
}
