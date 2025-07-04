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

/* void sig_handler(int sig)
{
    static int bit_count;
    static unsigned char c;

    bit_count = 0;
    c = 0;
    if(sig == SIGUSR1)
        c |= (1 << bit_count);
    bit_count++;

    if(bit_count == 8)
    {
        write(1,&c,1);  //  Da cambiare poi dopo
        bit_count = 0;
        c = 0;
        // TODO BONUS
    }
} */

void sig_handler(int sig)
{
    static int bit_count = 0;
    static unsigned char c = 0;

    if(sig == SIGUSR1)
        c |= (1 << (7 - bit_count));
    bit_count++;

    if(bit_count == 8)
    {
        write(1,&c,1);
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



