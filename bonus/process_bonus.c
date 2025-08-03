/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 12:20:35 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/03 14:23:28 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*get_cmd(char **path, char *cmd)
{
	char	*tmp;
	char	*cmd_finale;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		cmd_finale = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_finale, 0) == 0)
			return (cmd_finale);
		free(cmd_finale);
		i++;
	}
	return (NULL);
}

void	first_child(t_pipex *pipex, char **av, char **envp)
{
	if (pipex->fd_infile < 0)
		free_parent_exit(pipex);
	dup2(pipex->pipou[0][1], 1);
	dup2(pipex->fd_infile, 0);
	close(pipex->pipou[0][1]);
	close(pipex->pipou[0][0]);
	close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	pipex->cmd_args = ft_split(av[2], ' ');
	if (!pipex->cmd_args)
	{
		msg_error("Split cmd args failed");
		free_parent_exit(pipex);
	}
	pipex->cmd = get_cmd(pipex->path_final, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		msg_error("Not finding command with access");
		free_all_exit127(pipex);
	}
	execve(pipex->cmd, pipex->cmd_args, envp);
	msg_error("Execve not working");
	free_all(pipex);
	exit(1);
}

void	last_child(t_pipex *pipex, char **av, char **envp, int ac)
{
	if (pipex->fd_outfile < 0)
		free_parent_exit(pipex);
	dup2(pipex->pipou[ac - 5][1], 0);
	dup2(pipex->fd_outfile, 1);
	close(pipex->pipou[ac - 5][0]);
	close(pipex->pipou[ac - 5][1]);
	close(pipex->fd_outfile);
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	pipex->cmd_args = ft_split(av[ac - 3], ' ');
	if (!pipex->cmd_args)
	{
		msg_error("Split cmd args failed");
		free_parent_exit(pipex);
	}
	pipex->cmd = get_cmd(pipex->path_final, pipex->cmd_args[0]);
	if (!pipex->cmd)
	{
		msg_error("Not finding command with access");
		free_all_exit127(pipex);
	}
	execve(pipex->cmd, pipex->cmd_args, envp);
	msg_error("Execve not working");
	free_all(pipex);
	exit(1);
}


