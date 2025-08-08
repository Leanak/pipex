/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:16:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/08 15:28:13 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	forking(t_pipex *pipex, char **av, char **envp)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == 0)
		first_child(pipex, av, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		second_child(pipex, av, envp);
}

void	piping(t_pipex *pipex)
{
	if (pipe(pipex->pipou) < 0)
	{
		perror("Error with the pipe");
		close_fd(pipex);
		exit(1);
	}
}

void	opening(t_pipex *pipex, char **av, int ac)
{
	pipex->fd_infile = open(av[1], O_RDONLY);
	if (pipex->fd_infile < 0)
		perror("Infile not opening");
	pipex->fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
		perror("Outfile not opening");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		sortie;

	if (ac != 5)
		return (msg("Wrong number of arguments\n"));
	init_pipex(&pipex);
	opening(&pipex, av, ac);
	piping(&pipex);
	forking(&pipex, av, envp);
	close_fd_and_pipes(&pipex);
	waitpid(pipex.pid1, &sortie, 2);
	waitpid(pipex.pid2, &sortie, 2);
	return (WEXITSTATUS(sortie));
}
