/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:15:02 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/09 19:45:57 by lenakach         ###   ########.fr       */
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

char	*fill_path(char **path, char *cmd)
{
	char	*tmp;
	char	*cmd_finale;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			return (NULL);
		cmd_finale = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_finale)
			return (NULL);
		if (access(cmd_finale, X_OK) == 0)
		{
			free_split(path);
			return (cmd_finale);
		}
		free(cmd_finale);
		i++;
	}
	free_split(path);
	return (NULL);
}

char	*get_cmd(char *cmd, char **envp)
{
	char	**path;
	char	*path_tmp;
	int		i;
	char	*result;

	i = 0;
	if (!cmd || !*cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_tmp = find_path(envp);
	if (!path_tmp)
		return (NULL);
	path = ft_split(path_tmp, ':');
	if (!path)
		return (NULL);
	result = fill_path(path, cmd);
	return (result);
}
