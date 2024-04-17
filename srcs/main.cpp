/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:05:07 by maxime            #+#    #+#             */
/*   Updated: 2024/04/17 18:54:19 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <netinet/in.h>
#include <netdb.h>
// #include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>  
#include <sys/types.h> 
#include <sys/socket.h>  
#include <string.h> 
#include <stdio.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define NB_CLIENTS 5

int create_server(int port)
{
    int                 sock;
    struct protoent     *proto;
    struct sockaddr_in  sin;
    
    proto = getprotobyname("tcp");
    if (proto == 0)
    {
        printf("proto failed\n");
        return (-1);
    }
    sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
    if (sock == -1)
    {
        printf("socket failed\n");
        return (-1);
    }
    fcntl(sock, F_SETFL, O_NONBLOCK); /* Passe la socket en mode non bloquant: fortement deconseillé ça bouffe le CPU*/
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
    if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        // std::cout << "bind failed\n";
        return (-2);
    }
    listen(sock, 5);
    return (sock);    
}

void    loop_for_connection(int sock)
{
    int client_fd[NB_CLIENTS];
    struct sockaddr_in addr;
    int     size;
    fd_set  test;
    int     readed;
    char    buf[1024];
    struct timeval timeout;
    int     max;
    
    bzero(buf, 1024);
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    size = sizeof(struct sockaddr_in);
    
    for (int i = 0; i < NB_CLIENTS; i++)
        client_fd[i] = 0;
        
    while (1)
    {
        FD_ZERO(&test);
        FD_SET(sock, &test);
        max = sock;
        
        // Add child sockets to set
        for (int i = 0; i < NB_CLIENTS; i++)
        {
            if (client_fd[i] > 0) {
                FD_SET(client_fd[i], &test);
                if (client_fd[i] > max)
                    max = client_fd[i];
            }
        }
        int ready_to_read = select(max + 1, &test, NULL, NULL, &timeout);
        if (ready_to_read < 0)
            printf("select error");
        if (FD_ISSET(sock, &test))
        {
            int new_fd = accept(sock, (struct sockaddr *)&addr, (socklen_t *)&size);
            if (new_fd == -1)
            {
                printf("accept failed\n");
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
            if (FD_ISSET(client_fd[i], &test))
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
                            send(client_fd[j], buf, strlen(buf), 0);
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int                 port;
    int                 sock;
    
    if (argc != 2)
    {
        // std::cout << "usage :./exe <port> <password>\n";
        printf("usage :./exe <port> <password>\n");
        return (-1);
    }    
    port = atoi(argv[1]);
    sock = create_server(port);
    loop_for_connection(sock);
    close(sock);
    return (0);
}