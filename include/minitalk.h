/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvithara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:19:17 by tvithara          #+#    #+#             */
/*   Updated: 2025/06/19 20:19:22 by tvithara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../libft/includes/ft_printf.h"
# include "../libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

// SERVER
void	sig_handler(int sig, siginfo_t *info, void *context);
void	print_and_ack_bits(int *bit_count, unsigned char *c, pid_t *client_pid);

// CLIENT
void	send_char(pid_t pid, char c);
void	ack_handler(int sig);

#endif
