/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/18 15:17:22 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

Irc::Irc(void){};

Irc::Irc(const Irc &src) {

	*this = src;
}

Irc::Irc(const std::string port, const std::string password) {

	this->_port = atoi(port.c_str()); // temporary
	this->_password = password;
}

Irc::~Irc(void){};

Irc	&Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	this->_password = rhs._password;
	return (*this);
}

int Irc::getsocket() const {
	
	return this->_socket;
}

std::string Irc::getpassword() const {
	
	return this->_password;
}

int	Irc::getport() const {

	return this->_port;
}

int Irc::create_server()
{
    struct protoent     *proto;
    struct sockaddr_in  sin;
    
    proto = getprotobyname("tcp");
    if (proto == 0)
    {
        std::cerr << "proto failed\n";
        return (-1);
    }
    this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
    if (this->_socket == -1)
    {
        std::cerr << "socket failed\n";
        return (-1);
    }
    fcntl(this->_socket, F_SETFL, O_NONBLOCK); /* Passe la socket en mode non bloquant: fortement deconseillé ça bouffe le CPU*/
    sin.sin_family = AF_INET;
    sin.sin_port = htons(this->getport());
    sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
    if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
        std::cerr << "bind failed\n";
        return (-1);
    }
    listen(this->_socket, 5);
	return (0);
}

int    Irc::set_sockets(fd_set *set)
{
    int max = this->_socket;
    for (int i = 0; i < NB_CLIENTS; i++)
    {
        if (this->_user[i].getsocket() > 0) {
            FD_SET(this->_user[i].getsocket(), set);
            if (this->_user[i].getsocket() > max)
                max = this->_user[i].getsocket();
        }
    }
    return (max);
}

void    Irc::loop_for_connection()
{
    struct sockaddr_in addr;
    fd_set  set;
    int     size;
    int     readed;
    int     max;
    char    buf[1024];
    
    bzero(buf, 1024);
    size = sizeof(struct sockaddr_in);
    
    for (int i = 0; i < NB_CLIENTS; i++)
        this->_user[i].setsocket(0);
        
    while (1)
    {
        FD_ZERO(&set);
        FD_SET(this->_socket, &set);
        max = set_sockets(&set);
        int ready_to_read = select(max + 1, &set, NULL, NULL, NULL);
        if (ready_to_read < 0)
            printf("select error");
        if (FD_ISSET(this->_socket, &set))
        {
            int new_fd = accept(this->_socket, (struct sockaddr *)&addr, (socklen_t *)&size);
            if (new_fd == -1)
            {
                std::cerr << "accept failed\n";
                exit(EXIT_FAILURE);
            }
            for (int i = 0; i < NB_CLIENTS; i++)
            {
                if (this->_user[i].getsocket() == 0)
                {
                    this->_user[i].setsocket(new_fd);
					std::cout << "client nb " << i << " connected\n";
                    break;
                }
            }
        }
        for (int i = 0; i < NB_CLIENTS; i++)
        {
            if (FD_ISSET(this->_user[i].getsocket(), &set))
            {
                if ((readed = read(this->_user[i].getsocket(), buf, 1024)) == 0)
                {
                    close(this->_user[i].getsocket());
                    this->_user[i].setsocket(0);
					std::cout << "client nb " << i << " disconnected\n";
                }
                else
                {
                    for (int j = 0; this->_user[j].getsocket(); j++)
                    {
                        if (this->_user[i].getsocket() != this->_user[j].getsocket())
                            send(this->_user[j].getsocket(), buf, readed, 0);
                    }
                }
            }
        }
    }
}