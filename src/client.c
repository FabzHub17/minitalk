/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvithara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:20:38 by tvithara          #+#    #+#             */
/*   Updated: 2025/06/19 20:20:40 by tvithara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void send_char(pid_t pid, char c)
{
    int i;

    i = 7;
    while( i >= 0)
    {
        if((c >> i) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid,SIGUSR2);
        usleep(100); // Delay per sicurezza
        // TODO BONUS: qui potresti aspettare un segnale di ACK dal server
        i--;
    }

}

int main(int ac, char **av)
{
    if(ac != 3)
        return(1);
    
    pid_t pid;
    char *msg;
    int i;

    pid = atoi(av[1]); // DA CAMBIARE DOPO
    msg = av[2];
    i = 0;
    while(msg[i])
    {
        send_char(pid, msg[i]);
        i++;
    }
    
}