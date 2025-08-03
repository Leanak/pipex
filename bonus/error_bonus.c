/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 14:27:57 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/02 13:07:35 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	msg(char *error)
{
	write(2, error, ft_strlen(error));
	return (1);
}

int	msg_error(char *error)
{
	perror(error);
	return (1);
}
