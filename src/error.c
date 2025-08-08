/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:27:57 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/08 16:38:15 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

void	error_exit1(t_pipex *pipex, char *error)
{
	perror(error);
	free_child(pipex);
	exit(1);
}

void	error_exit127(t_pipex *pipex, char *error)
{
	perror(error);
	free_child(pipex);
	exit(127);
}
