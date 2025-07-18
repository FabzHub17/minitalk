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

static pid_t g_client_pid = 0;

void sig_handler(int sig, siginfo_t *info, void *context)
{
    static int bit_count = 0;
    static unsigned char c = 0;

    (void)context;

    // store client PID from first signal
    if(g_client_pid == 0)
        g_client_pid = info->si_pid;

    if(sig == SIGUSR1)
        c |= (1 << (7 - bit_count));
    //else if(sig == SIGUSR2)
    //    ; // bit 0, non serve modificare 'c'
    bit_count++;

    if(bit_count == 8)
    {
       
        if(c == '\0')
        {
            ft_printf("\n");
            //send acknowledgment back to client
            if(kill(g_client_pid, SIGUSR1) == -1)
                perror("kill");
            g_client_pid = 0; // reset for next message
        }
        else
        {
            ft_printf("%c",c);
            //send acknowledgment back to client
            if(kill(g_client_pid, SIGUSR1) == -1)
                perror("kill");
        }
        bit_count = 0;
        c = 0;
    }
    else
    {
        if(kill(g_client_pid, SIGUSR1) == -1)
             perror("kill");

    }

    
}


int main(void)
{
    struct sigaction sa; 
    ft_printf("The PID of the server is: %d\n", getpid());

    sa.sa_sigaction = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO; // use SA_SIGINFO to get sender PID

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while(1)
        pause(); 

    return(EXIT_SUCCESS);
}



