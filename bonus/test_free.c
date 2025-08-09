/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:49:56 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 15:55:47 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ultime_free_all(t_pipex *pipex, char *error, int count)
{
	perror(error);
	get_next_line(-1);
	free_parent(pipex);
	free_child(pipex);
	close_all_pipe(pipex, count);
	close_fd(pipex);
	exit(1);
}