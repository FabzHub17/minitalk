/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvithara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:20:38 by tvithara          #+#    #+#             */
/*   Updated: 2025/09/27 16:54:40 by tvithara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

void	print_error(char *mg)
{
	ft_printf(mg);
	exit(1);
}

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	send_char(pid_t pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_ack_received = 0;
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
				print_error("Error in sending signal\n");
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				print_error("Error in sending signal\n");
		}
		while (!g_ack_received)
			usleep(200);
		i--;
	}
}

int	main(int ac, char **av)
{
	pid_t				pid;
	char				*msg;
	int					i;
	struct sigaction	sa;

	if (ac != 3)
		return (1);
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	pid = ft_atoi(av[1]);
	msg = av[2];
	i = 0;
	while (msg[i])
	{
		send_char(pid, msg[i]);
		i++;
	}
	send_char(pid, '\0');
	return (EXIT_SUCCESS);
}
