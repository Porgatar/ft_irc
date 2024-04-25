/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/24 22:28:06 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Irc::Irc(void) : _socket(0), _password("") {

	std::cout << "Irc: default constructor\n";
};

Irc::Irc(const Irc &src) {

	std::cout << "Irc: copy constructor\n";
	*this = src;
}

int setNonBlocking(int fd) {

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return -1;
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1)
        return -1;
    return 0;
}

Irc::Irc(const std::string s_port, const std::string password) \
	: _socket(0), _password(password) {

	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					port;

	std::cout << "Irc: port/password constructor\n";
	port = atoi(s_port.c_str());
	if (port < 1024 || port > 65535) {
		std::cerr << PRED << "Error\nserver: port " << port \
			<< " is out of range\nrange: 1024 - 65535" << PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	proto = getprotobyname("tcp");
	if (proto == 0) {
		std::cerr << PRED << "Error\nserver: could not get prototype" \
			<< PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	this->_socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	if (this->_socket == -1) {
		std::cerr << PRED << "Error\nserver: could not get socket" \
			<< PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr("127.0.0.1"); /* inet return : network bytes order */
	if (bind(this->_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1) {
		std::cerr << PRED << "Error\nserver: could not bind" \
			<< PRESET << std::endl;
		exit(EXIT_FAILURE);
	}
	listen(this->_socket, 5);
	if (setNonBlocking(_socket) == -1) {
        std::cerr << PRED << "Error\nserver: could not switch to non-blocking listening" \
			<< PRESET << std::endl;
        exit(EXIT_FAILURE);
    }
}

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Irc::~Irc(void) {

	std::cout << "Irc: destructor\n";
	close(this->_socket);
}

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Irc &Irc::operator=(const Irc &rhs) {

	std::cout << "Irc: copy operator=\n";
	this->_socket = rhs._socket;
	this->_password = rhs._password;
	this->_users = rhs._users;
	this->_channels = rhs._channels;
	return (*this);
}

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/

int Irc::set_sockets(fd_set *set) {

	int max = this->_socket;
	std::list<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); ++it)
	{
		if (it->getSocket() > 0)
		{
			FD_SET(it->getSocket(), set);
			if (it->getSocket() > max)
				max = it->getSocket();
		}
	}
	return (max);
}

/*
// Check if it is a command and then set the rest of the command in the buffer
// return -1 if it is not
int	is_command(char *buf, std::list<User>::iterator actual) {

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
*/

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

void	Irc::join(std::list<User>::iterator actual) {

	// Channel newchannel();
	
}

void	Irc::nick(std::list<User>::iterator actual) {

	std::list<User>::iterator it;
	std::string argument = actual->getBuffer();
	
	if (argument.empty()){
		write(actual->getSocket(), " :No nickname given\n", 20);
		return ;
	}
	if (!rfc_nickname(argument)) {	
		write(actual->getSocket(), argument.c_str(), argument.length());
		write(actual->getSocket(), " :Erroneus nickname\n", 20);
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getNickname().compare(argument.c_str()) == 0) {
			write(actual->getSocket(), argument.c_str(), argument.length());
			write(actual->getSocket(), " :Nickname is already in use\n", 30);
			return ;
		}
	}
	actual->setNickname(argument);
}

void	Irc::user(std::list<User>::iterator actual) {

	//.
}

std::string	gettarget(std::string argument) {

	std::string target;
	int			i = 0;
	
	while (!((argument[i] >= 9 && argument[i] <= 13) || argument[i] == 32))
		i++;
	target = argument.substr(0, i);
	return (target);
}

std::string	skip_isspace(std::string str) {

	int	i;

	i = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32) // white space !
		i++;
	return (&str[i]);
}

void	Irc::privmsg(std::list<User>::iterator actual) {

	std::list<User>::iterator 	it;
	std::string 				argument;
	std::string					target;
	std::string					message;
	bool						finded;
	
	finded = false;
	argument = actual->getBuffer();
	target = gettarget(argument);
	if (target.empty()) {
		write(actual->getSocket(), " :No recipient given\n", 21);
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getNickname().compare(target.c_str()) == 0)
			finded = true;
	}
	if (!finded) {
		write(actual->getSocket(), target.c_str(), target.length());
		write(actual->getSocket(), " :No such nick\n", 15);
		return ;
	}
	message = argument.substr(target.length(), argument.length() - target.length());
	message = skip_isspace(message);
	if (message.empty()) {
		write(actual->getSocket(), " :No text to send\n", 18);
		return ;
	}
	// if (target[0] == '&' || target[0] == '#')
		//msg to channel
	write(it->getSocket(), message.c_str(), message.length());
	write(it->getSocket(),"\n", 1);
}

/*
void Irc::exec_command(int command_number, std::list<User>::iterator actual) {

	if (command_number == 1)
		join(actual);
	else if (command_number == 2)
		nick(actual);
	else if (command_number == 3)
		user(actual);
	else if (command_number == 4)
		privmsg(actual);
}
*/

void	remove_nl(char *str) {

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '\n')
			str[i] = '\0';
	}
}

void	Irc::exec_cmd(User &user) {

	if (user.isRegistered())
		std::cout << "received request from registered user(temporary print)\n";
	else
		std::cout << "received request from unregistered user(temporary print)\n";
	std::cout << PYELLOW << "server: request: " << user.getBuffer() << PRESET << "\n";

// call command for testing purpose here !!!
//	<command>(<args>);

	user.setBuffer("");
}

/*Look for any client message and parse it*/
void	Irc::is_writing(void) {

	std::list<User>::iterator	actual;
	std::list<User>::iterator	receiver;
	int							readed;
	int							command_number;
	char						buf[1024];

	memset(buf, '\0', 1024);
	for (actual = _users.begin(); actual != _users.end(); ++actual)
	{
		memset(buf, '\0', 1024);
		readed = recv(actual->getSocket(), buf, 1023, MSG_DONTWAIT);
//		remove_nl(buf);
		if (readed == 0)
		{
			close(actual->getSocket());
			std::cout << PRED << "server: client n°" << actual->getSocket() - 3 \
				<< " disconnected" << PRESET << "\n";
			actual = _users.erase(actual);
			actual--;
		}
//		else if ((command_number = is_command(buf, actual)) > -1) {
//			exec_command(command_number, actual);
//		}
//		else
//		{
		actual->setBuffer(actual->getBuffer() + std::string(buf));
		this->exec_cmd(*actual);
//		}
	}
}

void	Irc::init_new_user(int socket) {

//	char 	buf[12];
//	int		readed;
	User 	newuser;

//	memset(buf, '\0', 12);
//	write(socket, "password : ", 11);
//	while (_password.compare(buf) != 0)
//	{
//		memset(buf, '\0', 12);
//		readed = recv(socket, buf, 11, 0);
//		int endline = strlen(buf) - 1; 
//		if (buf[endline] == '\n')
//			buf[endline] = '\0';
//		is_writing();
//		if (_password.compare(buf) != 0 && readed != -1)
//			write(socket, "wrong password, try again\npassword : ", 38);
//	}
	newuser.setSocket(socket);
	_users.push_back(newuser);
}

void	Irc::loop_for_connection(void) {

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
		if (ready_to_read < 0) {
			printf("select failed\n");
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(this->_socket, &set)) {
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
