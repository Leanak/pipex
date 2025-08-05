/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lenakach <lenakach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:46:08 by lenakach          #+#    #+#             */
/*   Updated: 2025/08/05 12:46:28 by lenakach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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