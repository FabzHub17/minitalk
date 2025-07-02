/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvithara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:20:49 by tvithara          #+#    #+#             */
/*   Updated: 2025/06/19 20:20:52 by tvithara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
#include <stdio.h>

/*
    * The server process waits for signals from clients. (SIGUSR1 = 1 and SIGUSR2 = 0)
    * It prints the PID of the server process to the console.
    * IT needs to have handlers for the signals to process incoming data.
    * The server will run indefinitely, waiting for signals.
    * in computer science, a signal is a message that is sent to a process to indicate 
    * ->a particular event has occurred or to request a particular action to be taken. 
    * ->A process is a program that is being executed by the computer.
*/

void sig_handler(int sig)
{
    static int bit_count;
    static unsigned char c;

    bit_count = 0;
    c = 0;

    if(sig == SIGUSR1)
        c |= (1 << bit_count);
    if(bit_count == 8)
    {
        write(1,&c,1);  //  Da cambiare poi dopo
        bit_count = 0;
        c = 0;
        // TODO BONUS
    }
}


int main(void)
{
    struct sigaction sa; 
    //ft_printf("The PID of the server is: %d\n", getpid());
    printf("The PID of the server is: %d\n", getpid());

    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while(1)
        pause(); // Wait for signals

    return(EXIT_SUCCESS);
}


