/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:56:31 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/05 16:52:58 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex;
	int i;
	int sortie;

	i = 0;
	if (!*envp)
		return (1);
	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
		msg_error("Infile not opening");
	pipex.fd_outfile = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (pipex.fd_outfile < 0)
		msg_error("Outfile not opening");
	pipex.path = find_path(envp);
	if (!pipex.path)
	{
		close_fd(&pipex);
		msg_error("Probleme with find_path");
		exit(1);
	}
	pipex.path_final = ft_split(pipex.path, ':');
	if (!pipex.path_final)
	{
		close_fd(&pipex);
		msg_error("Probleme with path final split");
		exit(1);
	}
	first_pipe(&pipex, av, envp);
	inter_pipe(&pipex, av, ac, envp);
	last_pipe(&pipex, av, ac, envp);
	free_split(pipex.path_final);
	close_fd(&pipex);
	while (i < ac - 4)
	{
		waitpid(pipex.pid[i], &sortie, 2);
		i++;
	}
	//close_all_pipe(&pipex, ac - 4);
	return (WEXITSTATUS(sortie));
}