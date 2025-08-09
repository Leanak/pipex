/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:56:31 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 19:44:30 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	opening(t_pipex *pipex, char **av, int ac)
{
	if (pipex->start == 3)
	{
		pipex->fd_outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND,
				0777);
		handle_heredoc(av[2]);
		pipex->fd_infile = open(".heredoc_tmp", O_RDONLY);
		if (pipex->fd_infile < 0)
			perror("Heredoc tmp file not opening in main");
	}
	else if (pipex->start == 2)
	{
		pipex->fd_infile = open(av[1], O_RDONLY, 0777);
		if (pipex->fd_infile < 0)
			perror("Infile not opening");
		pipex->fd_outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT,
				0777);
		if (pipex->fd_outfile < 0)
			perror("Outfile not opening");
	}
}

void	init_pipex_bonus(t_pipex *pipex)
{
	pipex->path = NULL;
	pipex->path_final = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd = NULL;
}

static void	close_main(t_pipex *pipex)
{
	get_next_line(-1);
	close_fd(pipex);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		i;
	int		sortie;

	i = -1;
	init_pipex_bonus(&pipex);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		pipex.start = 3;
		opening(&pipex, av, ac);
	}
	else
	{
		pipex.start = 2;
		opening(&pipex, av, ac);
	}
	first_pipe(&pipex, av, envp);
	inter_pipe(&pipex, av, ac, envp);
	last_pipe(&pipex, av, ac, envp);
	while (++i < ac - 4)
		waitpid(pipex.pid[i], &sortie, 2);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		unlink(".heredoc_tmp");
	close_main(&pipex);
	return (WEXITSTATUS(sortie));
}
