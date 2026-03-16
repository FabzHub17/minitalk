/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvithara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:20:49 by tvithara          #+#    #+#             */
/*   Updated: 2025/09/27 16:55:30 by tvithara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	print_and_ack_bits(int *bit_count, unsigned char *c, pid_t *client_pid)
{
	if (*bit_count == 8)
	{
		if (*c == '\0')
		{
			ft_printf("\n");
			if (kill(*client_pid, SIGUSR1) == -1)
				ft_printf("Error\n");
			*client_pid = 0;
		}
		else
		{
			ft_printf("%c", *c);
			if (kill(*client_pid, SIGUSR1) == -1)
				ft_printf("Error\n");
		}
		*bit_count = 0;
		*c = 0;
	}
	else
		kill(*client_pid, SIGUSR1);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	c = 0;
	static pid_t			client_pid = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		c |= (1 << (7 - bit_count));
	bit_count++;
	print_and_ack_bits(&bit_count, &c, &client_pid);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("The PID of the server is: %d\n", getpid());
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
