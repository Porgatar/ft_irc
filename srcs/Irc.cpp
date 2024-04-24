/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/24 15:11:31 by maxime           ###   ########.fr       */
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

static int setNonBlocking(int fd)
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
	if (port > 65535) {
		std::cerr << "port number too large: " << port << std::endl;
		exit(EXIT_FAILURE);
	}
	proto = getprotobyname("tcp");
	if (proto == 0) {
		std::cerr << "proto failed\n";
		exit(EXIT_FAILURE);
	}
	this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1) {
		std::cerr << "socket failed\n";
		exit(EXIT_FAILURE);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
	if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1) {
		std::cerr << "bind failed\n";
		exit(EXIT_FAILURE);
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

// Check if it is a command and then set the rest of the command in the buffer
// return -1 if it is not
int	is_command(char *buf, std::list<User>::iterator actual)
{
	int i = 0;
	int j = 0;
	std::string cmd[4] = {"JOIN", "NICK", "USER", "PRIVMSG"};
	char	command[9];

	memset(command, '\0', 9);
	while (buf[i] >= 9 && buf[i] <= 13 || buf[i] == 32) // white space !
		i++;
	while (isalnum(buf[i]))
	{
		command[j] = buf[i];
		i++;
		j++;
	}
	for (int j = 0; j < 4; j++)
	{
		if (cmd[j].compare(command) == 0)
		{
			actual->setbuffer(&buf[i + 1]);
			return (j + 1);
		}
	}
	return (-1);
}

/*return true if the nickname respect the norm*/
bool rfc_nickname(const std::string& str) {
	
    const std::string set = "([{{|\\}}])";

    for (int i = 0; str[i]; i++) {
        if (isalnum(str[i]) || set.find(str[i]) != std::string::npos)
            continue;
        else
			return false;
    }
    return true;
}

void	Irc::join(std::list<User>::iterator actual)
{
	// Channel newchannel();
	
}

void	Irc::nick(std::list<User>::iterator actual)
{
	std::list<User>::iterator it;
	std::string argument = actual->getbuffer();
	
	if (!rfc_nickname(argument)) {	
		write(actual->getsocket(), "Bad nickname character\n", 23);
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getnickname().compare(argument.c_str()) == 0) {
			write(actual->getsocket(), argument.c_str(), argument.length());
			write(actual->getsocket(), " : Nickname is already in use\n", 30);
			return ;
		}
	}
	actual->setnickname(argument);
}

void	Irc::user(std::list<User>::iterator actual)
{
	
}

void	Irc::privmsg(std::list<User>::iterator actual)
{
	
}

void Irc::exec_command(int command_number, std::list<User>::iterator actual)
{
	if (command_number == 1)
		join(actual);
	else if (command_number == 2)
		nick(actual);
	else if (command_number == 3)
		user(actual);
	else if (command_number == 4)
		privmsg(actual);

}

void	remove_nl(char *str)
{
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '\n')
			str[i] = '\0';
	}
}

/*Look for any client message and parse it*/
void Irc::is_writing()
{
	std::list<User>::iterator actual;
	std::list<User>::iterator receiver;
	int readed;
	int	command_number;
	char buf[1024];

	memset(buf, '\0', 1024);
	for (actual = _users.begin(); actual != _users.end(); ++actual)
	{
		memset(buf, '\0', 1024);
		readed = recv(actual->getsocket(), buf, 1023, 0);
		remove_nl(buf);
		if (readed == 0)
		{
			close(actual->getsocket());
			std::cout << "client n°" << actual->getsocket() - 3 << " disconnected\n";
			actual = _users.erase(actual);
			actual--;
		}
		else if ((command_number = is_command(buf, actual)) > -1) {
			exec_command(command_number, actual);
		}
		else
		{
			actual->setbuffer(buf);
			actual->send_message(_users);
		}
	}
}

void	Irc::init_new_user(int socket)
{
	char 	buf[12];
	int		readed;
	User 	newuser;
	
	memset(buf, '\0', 12);
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
	newuser.setsocket(socket);
	_users.push_back(newuser);
}

void Irc::loop_for_connection()
{
	struct sockaddr_in	addr;
	fd_set				set;
	int					size;
	int					max;

	size = sizeof(struct sockaddr_in);
	while (1)
	{
		FD_ZERO(&set);
		FD_SET(this->_socket, &set);
		max = set_sockets(&set);
		int ready_to_read = select(max + 1, &set, NULL, NULL, NULL); // attente d'une connection sur la socket
		if (ready_to_read < 0){
			printf("select failed\n");
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(this->_socket, &set))
		{
			int new_fd = accept(this->_socket, (struct sockaddr *)&addr, (socklen_t *)&size);
			if (new_fd == -1) {
				std::cerr << "accept failed\n";
				exit(EXIT_FAILURE);
			}
			if (setNonBlocking(new_fd) == -1) {
        		std::cerr << "Failed to set client socket to non-blocking\n";
				exit(EXIT_FAILURE);
    		}
			init_new_user(new_fd);
			std::cout << "client n°" << new_fd - 3 << " connected\n";
		}
		is_writing();
	}
}
