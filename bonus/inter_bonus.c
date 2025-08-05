/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:58:40 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/05 14:37:10 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	inter_pipe(t_pipex *pipex, char **av, int ac, char **envp)
{
	int	i;
	int	j;

	i = 1;
	j = 3;
	while (i < ac - 4)
	{
		printf("NEW COMMAND et mon i : %d\n", i);
		if (pipe(pipex->pipou[i]) < 0)
		{
			msg_error("pipe I not working");
			close_fd(pipex);
			exit(1);
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
				free_parent(pipex);
				exit(1);
			}
			pipex->cmd = get_cmd(pipex->path_final, pipex->cmd_args[0]);
			if (!pipex->cmd)
			{
				perror("Not finding cmd i");
				free_all(pipex);
				exit(127);
			}
			execve(pipex->cmd, pipex->cmd_args, envp);
			msg_error("HOLA Execve not working");
			free_all(pipex);
			exit(1);
		}
		else
		{
			// close(pipex->pipou[i][1]);
			close(pipex->pipou[i - 1][0]);
			close(pipex->pipou[i - 1][1]);
		}
		i++;
		j++;
	}
}
