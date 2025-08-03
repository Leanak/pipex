/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:12:46 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/03 15:12:43 by lenakach         ###   ########.fr       */
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

void	last_pipe(t_pipex *pipex, char **av, char **envp, int ac)
{
	pipex->pid[ac - 3] = fork();
	if (pipex->pid[ac - 3] == 0)
		last_child(pipex, av, envp, ac);
}

void	inter_pipe(t_pipex *pipex, char **av, char **envp, int ac)
{
	int	i;
	int	j;

	i = 1;
	j = 3;
	while (i < ac - 4)
	{
		if (pipe(pipex->pipou[i]) < 0)
		{
			msg_error("Error with the pipe");
			close_fd(pipex);
		}
		pipex->pid[i] = fork();
		if (pipex->pid[i] == 0)
		{
			dup2(pipex->pipou[i][1], 1);
			dup2(pipex->pipou[i - 1][0], 0);
			close(pipex->pipou[i][1]);
			close(pipex->pipou[i][0]);
			close(pipex->pipou[i - 1][0]);
			close(pipex->pipou[i - 1][1]);
			pipex->cmd_args = ft_split(av[j], ' ');
			if (!pipex->cmd_args)
			{
				msg_error("Split cmd args failed");
				free_parent_exit(pipex);
			}
			pipex->cmd = get_cmd(pipex->path_final, pipex->cmd_args[0]);
			if (!pipex->cmd)
			{
				msg_error("int Not finding command with access");
				free_all_exit127(pipex);
			}
			execve(pipex->cmd, pipex->cmd_args, envp);
			msg_error("Execve not working");
			free_all(pipex);
			exit(1);
		}
		i++;
		j++;
	}
}

void	first_pipe(t_pipex *pipex, char **av, char **envp)
{
	if (pipe(pipex->pipou[0]) < 0)
	{
		msg_error("Error with the pipe");
		close_fd(pipex);
	}
	pipex->pid[0] = fork();
	if (pipex->pid[0] == 0)
		first_child(pipex, av, envp);
	else if (pipex->pid[0] > 0)
		close(pipex->pipou[0][1]);
	else
		msg_error("Fork Failed");
}

int	main(int ac, char **av, char **envp)
{
	t_pipex pipex = {0};

	pipex.fd_infile = open(av[1], O_RDONLY);
	if (pipex.fd_infile < 0)
		msg_error("Infile not opening");
	pipex.fd_outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex.fd_outfile < 0)
		msg_error("Outfile not opening");
	pipex.path = find_path(envp);
	if (!pipex.path)
	{
		close_fd(&pipex);
		msg_error("Path not find in envp");
	}
	pipex.path_final = ft_split(pipex.path, ':');
	first_pipe(&pipex, av, envp);
	
	inter_pipe(&pipex, av, envp, ac);
	last_pipe(&pipex, av, envp, ac);
	free_parent(&pipex);
}