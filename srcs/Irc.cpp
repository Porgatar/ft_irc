/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/20 03:24:13 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

Irc::Irc(void) : _socket(0), _password(""), /*_user(0),*/ _channel(0) {};

Irc::Irc(const Irc &src) {

	*this = src;
}
Irc::Irc(const std::string s_port, const std::string password) : \
			_socket(0), _password(password), /*_user(0),*/ _channel(0) {

	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					port;

	port = atoi(s_port.c_str());
	proto = getprotobyname("tcp");
	if (proto == 0)
	{
		std::cerr << "proto failed\n";
		return ;
	}
	this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1)
	{
		std::cerr << "socket failed\n";
		return ;
	}
	fcntl(this->_socket, F_SETFL, O_NONBLOCK); /* Passe la socket en mode non bloquant: fortement deconseillé ça bouffe le CPU*/
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
	if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		std::cerr << "bind failed\n";
	 	return ;
	}
	listen(this->_socket, 5);
}

Irc::~Irc(void) {

	close(this->_socket);
};

Irc	&Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	this->_password = rhs._password;
	return (*this);
}

int	Irc::getsocket() const {

	return this->_socket;
}

std::string	Irc::getpassword() const {

	return this->_password;
}

int	Irc::set_sockets(fd_set *set)
{
	int max = this->_socket;
    std::vector<User>::iterator it;

	for (it = _user.begin(); it != _user.end(); ++it)
	{
		if (it->getsocket() > 0) {
			FD_SET(it->getsocket(), set);
			if (it->getsocket() > max)
				max = it->getsocket();
		}
	}
	return (max);
}

void    Irc::send_message(fd_set *set)
{
    std::vector<User>::iterator it;
    std::vector<User>::iterator ite;
    int                         readed;
	char                        buf[1024];
    
	memset(buf, '\0', 1024);
	for (it = _user.begin(); it != _user.end(); ++it)
	{
		if (FD_ISSET(it->getsocket(), set))
		{
			if ((readed = read(it->getsocket(), buf, 1024)) == 0)
			{
				close(it->getsocket());
				std::cout << "client n°" << it->getsocket() - 3 << " disconnected\n";
				it->setsocket(0);
			}
			else
			{
				for (ite = _user.begin(); ite != _user.end(); ++ite)
				{
					if (it->getsocket() != ite->getsocket())
						send(ite->getsocket(), buf, readed, 0);
				}
			}
		}
	}
}

/*              TO DO : 
faire en sorte que les clients deja connecter puisse continuer a envoyer des messages,
 meme si celui ci est en train de se connecter*/
void    Irc::init_new_user(int socket)
{
	char    buf[60000];
    char    nickname[11];
    char    username[11];
    
	memset(buf, '\0', 60000);
	memset(nickname, '\0', 11);
	memset(username, '\0', 11);
    write(socket, "password : ", 11);   
    while (read(socket, buf, 60000) && _password.compare(buf) != 0)
    {
        char endline = strlen(buf) - 1;
        buf[endline] = '\0';
        if (_password.compare(buf) == 0)
            break;
        write(socket, "wrong password, try again\npassword : ", 38);
    }
    write(socket, "nickname : ", 11);
    read(socket, nickname, 10);
    write(socket, "username : ", 11);
    read(socket, nickname, 10);
    User newuser(socket, (std::string)username, (std::string)nickname);
    // newuser.setsocket(socket);
    _user.push_back(newuser);
    
}

void    Irc::loop_for_connection()
{
	struct sockaddr_in  addr;
	fd_set              set;
	int                 size;
	int                 max;

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
            init_new_user(new_fd);
            
			std::cout << "client n°" << new_fd - 3 << " connected\n";
		}
        send_message(&set);
	}
}
