/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:16:37 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/06 16:38:56 by lenakach         ###   ########.fr       */
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

void	opening(t_pipex *pipex, char **av, int ac)
{
	pipex->fd_infile = open(av[1], O_RDONLY);
	if (pipex->fd_infile < 0)
		msg_error("Infile not opening");
	pipex->fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd_outfile < 0)
		msg_error("Outfile not opening");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		sortie;

	if (!*envp)
		return (1);
	if (ac != 5)
		return (msg("Wrong number of arguments\n"));
	opening(&pipex, av, ac);
	piping(&pipex);
	pipex.path = find_path(envp);
	if (!pipex.path)
	{
		msg_error("Path not find in envp");
		close_fd_and_pipes(&pipex);
	}
	pipex.path_final = ft_split(pipex.path, ':');
	forking(&pipex, av, envp);
	close_pipes(&pipex);
	waitpid(pipex.pid1, &sortie, 2);
	waitpid(pipex.pid2, &sortie, 2);
	free_parent(&pipex);
	return (WEXITSTATUS(sortie));
}
