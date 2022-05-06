/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okumurahyu <okumurahyu@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 22:53:51 by okumurahyu        #+#    #+#             */
/*   Updated: 2022/04/24 11:06:30 by hokumura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_sig_receive[2];

static void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	g_sig_receive[0] = info->si_pid;
	if (sig == SIGUSR1)
		g_sig_receive[1] = 0;
	else if (sig == SIGUSR2)
		g_sig_receive[1] = 1;
}

static void	set_signal(void)
{
	struct sigaction	act;
	int					fg_err;

	fg_err = 0;
	ft_bzero(&act, sizeof(struct sigaction));
	act.sa_sigaction = &sig_handler;
	act.sa_flags = SA_SIGINFO;
	sigemptyset(&(act.sa_mask));
	fg_err += sigaction(SIGUSR1, &act, NULL);
	fg_err += sigaction(SIGUSR2, &act, NULL);
	if (fg_err)
		exit(1);
}

static char	sig_to_c(void)
{
	size_t	i;
	size_t	power;
	char	c;

	i = 0;
	power = 1;
	c = 0;
	while (i < 8)
	{
		pause();
		c += g_sig_receive[1] * power;
		power *= 2;
		i++;
	}
	return (c);
}

static void	receive_sig(void)
{
	char	c;
	char	*str;
	int		fg_err;

	str = (char *)ft_xmalloc(sizeof(char) * 1);
	str[0] = '\0';
	fg_err = 0;
	while (1)
	{
		c = sig_to_c();
		if (c == 4)
			break ;
		str = ft_stradd_char(&str, c);
		usleep(200);
		fg_err += kill(g_sig_receive[0], SIGUSR1);
		if (fg_err)
		{
			free(str);
			exit(1);
		}
	}
	ft_putstr_fd(str, STDOUT_FILENO);
	free(str);
	receive_sig();
}

int	main(void)
{
	print_pid();
	set_signal();
	receive_sig();
}
