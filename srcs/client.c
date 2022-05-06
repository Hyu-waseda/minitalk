/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 15:06:35 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/24 10:53:02 by okumurahyu       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	sig_handler(int sig)
{
	if (sig == SIGUSR1)
		;
	else if (sig == SIGUSR2)
		;
}

static void	set_signal(void)
{
	struct sigaction	act;
	int					fg_err;

	fg_err = 0;
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	sigemptyset(&(act.sa_mask));
	fg_err += sigaction(SIGUSR1, &act, NULL);
	fg_err += sigaction(SIGUSR2, &act, NULL);
	if (fg_err)
		exit(1);
}

static int	is_valid_pid(char *pid)
{
	size_t	i;

	if (ft_strlen(pid) > 9 || pid[0] == 0)
		return (0);
	i = 0;
	while (ft_isdigit(pid[i]))
		i++;
	if (i != ft_strlen(pid))
		return (0);
	return (1);
}

void	validate(int argc, char **argv)
{
	if (argc != 3)
		exit(1);
	else if (!is_valid_pid(argv[1]))
		exit(1);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	size_t	i;

	validate(argc, argv);
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		exit(1);
	set_signal();
	i = 0;
	while (argv[2][i] != '\0')
	{
		sent_char(argv[2][i], pid);
		i++;
		pause();
	}
	sent_char(4, pid);
}
