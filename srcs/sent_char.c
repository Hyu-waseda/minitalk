/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sent_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 10:52:34 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/24 10:54:08 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sent_char(char c, pid_t pid)
{
	size_t	i;
	int		fg_err;

	fg_err = 0;
	i = 0;
	while (i < 8)
	{
		usleep(220);
		if (((c >> i) & 1) == 0)
			fg_err += kill(pid, SIGUSR1);
		else
			fg_err += kill(pid, SIGUSR2);
		i++;
		if (fg_err)
			exit(1);
	}
}
