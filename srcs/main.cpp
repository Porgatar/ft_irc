/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/04/18 12:14:02 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/types.h> 
#include <sys/socket.h>  
#include <string.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "../headers/Irc.hpp"


int    set_sockets(int sock, int client_fd[], fd_set *set)
{
    int max = sock;
    
    for (int i = 0; i < NB_CLIENTS; i++)
    {
        if (client_fd[i] > 0) {
            FD_SET(client_fd[i], set);
            if (client_fd[i] > max)
                max = client_fd[i];
        }
    }
    return (max);
}

void    loop_for_connection(int sock)
{
    int client_fd[NB_CLIENTS];
    struct sockaddr_in addr;
    int     size;
    fd_set  set;
    int     readed;
    char    buf[1024];
    int     max;
    
    bzero(buf, 1024);
    size = sizeof(struct sockaddr_in);
    
    for (int i = 0; i < NB_CLIENTS; i++)
        client_fd[i] = 0;
        
    while (1)
    {
        FD_ZERO(&set);
        FD_SET(sock, &set);
        max = set_sockets(sock, client_fd, &set);
        int ready_to_read = select(max + 1, &set, NULL, NULL, NULL);
        if (ready_to_read < 0)
            printf("select error");
        if (FD_ISSET(sock, &set))
        {
            int new_fd = accept(sock, (struct sockaddr *)&addr, (socklen_t *)&size);
            if (new_fd == -1)
            {
                std::cerr << "accept failed\n";
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < NB_CLIENTS; i++)
            {
                if (client_fd[i] == 0)
                {
                    client_fd[i] = new_fd;
                    break;
                }
            }
        }
        for (int i = 0; i < NB_CLIENTS; i++)
        {
            if (FD_ISSET(client_fd[i], &set))
            {
                if ((readed = read(client_fd[i], buf, 1024)) == 0)
                {
                    // Client disconnected
                    close(client_fd[i]);
                    client_fd[i] = 0;
                }
                else
                {
                    for (int j = 0; client_fd[j]; j++)
                    {
                        if (client_fd[i] != client_fd[j])
                            send(client_fd[j], buf, readed, 0);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "usage :./exe <port> <password>\n";
        return (-1);
    }
    
    Irc irc(argv[1], "password");
    
    if (irc.create_server(irc.getport()) == -1)
    {
        std::cerr << "server failed\n";   
        return (-1);
    }
    loop_for_connection(irc.getsocket());
    // close(sock);
    return (0);
}