/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:16:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/02 11:49:17 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

void	close_pipes(t_pipex pipex)
{
	close(pipex.pipou[0]);
	close(pipex.pipou[1]);
}

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
	close_pipes(*pipex);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		sortie;

	if (ac != 5)
		return (msg("Wrong number of arguments\n"));
	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
		msg_error("Infile not opening");
	pipex.fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.fd_outfile < 0)
		msg_error("Outfile not opening");
	piping(&pipex);
	pipex.path = find_path(envp);
	if (!pipex.path)
	{
		close_fd_and_pipes(&pipex);
		msg_error("Path not find in envp");
	}
	pipex.path_final = ft_split(pipex.path, ':');
	forking(&pipex, av, envp);
	close_pipes(pipex);
	waitpid(pipex.pid1, &sortie, 2);
	waitpid(pipex.pid2, &sortie, 2);
	free_parent(&pipex);
	return (WEXITSTATUS(sortie));
}
