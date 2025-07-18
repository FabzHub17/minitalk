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

static volatile sig_atomic_t g_ack_received = 0;

void ack_handler(int sig)
{
    (void)sig;
    g_ack_received = 1;
}

void send_char(pid_t pid, char c)
{
    int i;

    i = 7;
    while( i >= 0)
    {
        g_ack_received = 0;

        if((c >> i) & 1)
        {   
            if(kill(pid, SIGUSR1) == -1)
                perror("kill");

        }
        else
        {
            if(kill(pid, SIGUSR2) == -1)
                perror("kill");
        }
        
        // wait for acknowledgment from server
        while(!g_ack_received)
            usleep(500); 
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
    struct sigaction sa;

    // set up signal handler for acknowledgtements
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGUSR1,&sa,NULL);

    pid = ft_atoi(av[1]); 
    msg = av[2];
    i = 0;
    while(msg[i])
    {
        send_char(pid, msg[i]);
        i++;
    }
    send_char(pid, '\0'); // Send null terminator

    return(EXIT_SUCCESS);
    
}