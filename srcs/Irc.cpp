/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/22 17:41:01 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

Irc::Irc(void) : _socket(0), _password("") {

	std::cout << "Irc: default constructor\n";
};

Irc::Irc(const Irc &src)
{

	std::cout << "Irc: copy constructor\n";
	*this = src;
}
// 
// Irc::Irc(const std::string s_port, const std::string password) : \
// 			_socket(0), _password(password) {

int setNonBlocking(int fd)
{
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1)
        return -1;
    return 0;
}

Irc::Irc(const std::string s_port, const std::string password) : _socket(0), _password(password) /*_user(0),*/ //_channel(0)
{

	struct protoent *proto;
	struct sockaddr_in sin;
	int port;

	std::cout << "Irc: port/password constructor\n";
	port = atoi(s_port.c_str());
	proto = getprotobyname("tcp");
	if (proto == 0)
	{
		std::cerr << "proto failed\n";
		return;
	}
	this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1)
	{
		std::cerr << "socket failed\n";
		return;
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
	if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "bind failed\n";
		return;
	}
	listen(this->_socket, 5);
	if (setNonBlocking(_socket) == -1) {
        std::cerr << "Failed to set server socket to non-blocking\n";
        exit(EXIT_FAILURE);
    }
}

Irc::~Irc(void)
{
	close(this->_socket);
}

Irc &Irc::operator=(const Irc &rhs)
{

	std::cout << "Irc: copy operator=\n";
	this->_socket = rhs._socket;
	this->_password = rhs._password;
	this->_users = rhs._users;
	this->_channels = rhs._channels;
	return (*this);
}

int Irc::getsocket() const
{

	return this->_socket;
}

std::string Irc::getpassword() const
{

	return this->_password;
}

int Irc::set_sockets(fd_set *set)
{
	int max = this->_socket;
	std::list<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->getsocket() > 0)
		{
			FD_SET(it->getsocket(), set);
			if (it->getsocket() > max)
				max = it->getsocket();
		}
	}
	return (max);
}

void Irc::is_writing()
{
	std::list<User>::iterator actual;
	std::list<User>::iterator receiver;
	int readed;
	char buf[1024];

	memset(buf, '\0', 1024);
	for (actual = _users.begin(); actual != _users.end(); ++actual)
	{
		memset(buf, '\0', 1024);
		if ((readed = recv(actual->getsocket(), buf, 1023, 0)) == 0)
		{
			close(actual->getsocket());
			std::cout << "client n°" << actual->getsocket() - 3 << " disconnected\n";
			actual = _users.erase(actual);
			actual--;
		}	
		else
		{
			actual->setbuffer(buf);
			actual->send_message(_users);
			
		}
	}
}

void	Irc::init_new_user(int socket, fd_set *set)
{
	char buf[12];
	char nickname[11];
	char username[11];
	int readed;
	
	memset(buf, '\0', 12);
	memset(nickname, '\0', 11);
	memset(username, '\0', 11);
	write(socket, "password : ", 11);
	while (_password.compare(buf) != 0)
	{
		memset(buf, '\0', 12);
		readed = recv(socket, buf, 11, 0);
		int endline = strlen(buf) - 1; 
		if (buf[endline] == '\n')
			buf[endline] = '\0';
		is_writing();
		if (_password.compare(buf) != 0 && readed != -1)
			write(socket, "wrong password, try again\npassword : ", 38);
	}
	write(socket, "nickname : ", 11);
	while (!nickname[0])
	{
		is_writing();
		readed = recv(socket, nickname, 10, 0);
	}
	write(socket, "username : ", 11);
	while (!username[0])
	{
		is_writing();
		recv(socket, username, 10, 0);
	}
	User newuser(socket, (std::string)username, (std::string)nickname);
	_users.push_back(newuser);
	
}

void Irc::loop_for_connection()
{
	struct sockaddr_in addr;
	fd_set set;
	int size;
	int max;

	size = sizeof(struct sockaddr_in);
	while (1)
	{
		FD_ZERO(&set);
		FD_SET(this->_socket, &set);
		max = set_sockets(&set);
		int ready_to_read = select(max + 1, &set, NULL, NULL, NULL); // attente d'une connection sur la socket
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
			if (setNonBlocking(new_fd) == -1) {
        		std::cerr << "Failed to set client socket to non-blocking\n";
    		}
			init_new_user(new_fd, &set);

			std::cout << "client n°" << new_fd - 3 << " connected\n";
		}
		is_writing();
	}
}
