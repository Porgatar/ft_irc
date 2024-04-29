/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/29 13:18:01 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Irc.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Irc::Irc(void) : _socket(0), _password("") {};

Irc::Irc(const Irc &src) {

	*this = src;
}

Irc::Irc(const std::string s_port, const std::string password) \
	: _socket(0), _password(password) {

	struct protoent		*proto;
	struct sockaddr_in	sin;
	int					port;

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
}

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Irc::~Irc(void) {

	this->_users.clear();
	this->_channels.clear();
	close(this->_socket);
}

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Irc &Irc::operator=(const Irc &rhs) {

	this->_socket = rhs._socket;
	this->_password = rhs._password;
	this->_users = rhs._users;
	this->_channels = rhs._channels;
	return (*this);
}

/*	-	-	-	-	-	Private Functions	-	-	-	-	-	*/

int Irc::setSockets(fd_set *set) {

	int max = this->_socket;
	std::list<User>::iterator it;

	for (it = _users.begin(); it != _users.end(); ++it) {

		if (it->getSocket() > 0) {

			FD_SET(it->getSocket(), set);
			if (it->getSocket() > max)
				max = it->getSocket();
		}
	}
	return (max);
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

bool	Irc::check_existing_channel(std::string channels_name, User &user)
{
	std::list<Channel>::iterator		it;

	for (it = _channels.begin(); it != _channels.end(); it++) {
		if (it->getName().compare(channels_name.c_str()) == 0) {
			if (it->user_already_in(user) == false) {
				it->add_user(user);
				it->send_group_msg(user.getNickname() + " is joining the channel " + it->getName() + "\n");
			}
			return (true);
		}
	}
	return (false);
}

void	Irc::join(User &user) {
	
	Channel channel;
	std::list<std::string>::iterator	it;
    std::list<std::string> 				cmds;
    std::string 						argument = user.getBuffer();

    argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
    if (argument[0] != '&' && argument[0] != '#') {
        write(user.getSocket(), "Channel begin with & or #\n", 26); // TEMPORAIRE
        return;
    }
    size_t start = 0;
    size_t end = 0;
    while (end < argument.size() && argument[end] != ' ') {
        while (end < argument.size() && argument[end] != '&' && argument[end] != '#') {
            end++;
        }
        if (end < argument.size()) {
            size_t next = end + 1;
            while (next < argument.size() && argument[next] != ',' && argument[next] != ' ')
                next++;
			if (argument[next] == ',' && argument[next + 1] != '&' && argument[next + 1] != '#') {

				write(user.getSocket(), "no comma allowed\n", 17);
				return ;
			}
			/*si argument [next] == espace, regarder si il ya une clé apres, sinon retourner une erreur*/
            std::string channel_name = argument.substr(start, next - start);
            cmds.push_back(channel_name);
            start = next + 1;
        }
        end = start;
    }
	for (it = cmds.begin(); it != cmds.end(); it++) {
		if (!(check_existing_channel(*it, user))) {
			Channel channel(*it, user);
			_channels.push_back(channel);
			channel.send_group_msg(user.getNickname() + " is joining the channel " + channel.getName() + "\n");
		}
	}
}

void	Irc::nick(User &actual) {

	std::list<User>::iterator it;
	std::string argument = actual.getBuffer();
	
	argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
	if (argument.empty()){
		write(actual.getSocket(), " :No nickname given\n", 20);
		return ;
	}
	if (!rfc_nickname(argument)) {	
		write(actual.getSocket(), argument.c_str(), argument.length());
		write(actual.getSocket(), " :Erroneus nickname\n", 20);
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getNickname().compare(argument.c_str()) == 0) {
			write(actual.getSocket(), argument.c_str(), argument.length());
			write(actual.getSocket(), " :Nickname is already in use\n", 30);
			return ;
		}
	}
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) && actual.getNickname().empty()) {
		actual.setHigherRegisteredLevel();
		actual.setNickname(argument);
	}
}

// a l'appel de pass, verifier si on est pas deja connecter, pareil pour USER et NICK
void	Irc::pass(User &actual)
{
	std::string argument = actual.getBuffer();
	argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
	argument = skip_isspace(argument);
	if (argument.empty())
		write(actual.getSocket(), "PASS :Not enough parameters\n", 28); //test avec la commande PASS seule a verifier
	else if (argument.compare(_password) == 0){
		if (actual.getRegisteredLevel() == 0) 
			actual.setHigherRegisteredLevel();
	}
	else {
		actual.setLowerRegisteredLevel();
		write(actual.getSocket(), " :Password incorrect\n", 21);
	}
}

void	Irc::user_cmd(User &actual) {

	//.	argument.erase(std::remove(argument.begin(), argument.end(), '\n'), argument.end());
	if ((actual.getRegisteredLevel() == 2 || actual.getRegisteredLevel() == 1) && actual.getUsername() == "") {
		actual.setHigherRegisteredLevel();
		actual.setUsername(actual.getBuffer());
	}
}

void	Irc::privmsg(User &actual) {
	std::list<User>::iterator 	it;
	std::string 				argument;
	std::string					target;
	std::string					message;
	bool						finded;
	
	finded = false;
	argument = actual.getBuffer();
	target = gettarget(argument);
	if (target.empty()) {
		write(actual.getSocket(), " :No recipient given\n", 21);
		return ;
	}
	for (it = _users.begin(); it != _users.end(); it++) {
		if (it->getNickname().compare(target.c_str()) == 0)
			finded = true;
	}
	message = argument.substr(target.length(), argument.length() - target.length());
	message = skip_isspace(message);
	if (message.empty()) {
		write(actual.getSocket(), " :No text to send\n", 18);
		return ;
	}
	if (target[0] == '&' || target[0] == '#') {
		finded = true;
		for (std::list<Channel>::iterator ite = _channels.begin(); ite != _channels.end(); ite++) {
			if (ite->getName().compare(target.c_str()) == 0) {
				ite->send_group_msg(message);
				return ;
			}
		}
		// write(actual.getSocket(), "")
	}
	if (!finded ) {
		write(actual.getSocket(), target.c_str(), target.length());
		write(actual.getSocket(), " :No such nick\n", 15);
		return ;
	}
	write(it->getSocket(), message.c_str(), message.size());
	write(it->getSocket(),"\n", 1);
}

// Check if it is a command and then set the rest of the command in the buffer
// return -1 if it is not
int	is_command(std::string buf, User &actual) {

	int i = 0;
	std::string cmd[5] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN"};
	char	command[9];

	memset(command, '\0', 9);
	buf = skip_isspace(buf);
	while (isalnum(buf[i]))
	{
		command[i] = buf[i];
		i++;
	}
	for (int j = 0; j < 5; j++)
	{
		if (cmd[j].compare(command) == 0)
		{
			actual.setBuffer(&buf[i + 1]); // a voir si il ne faut pas effacer le buffer avant
			return (j + 1);
		}
	}
	return (-1);
}

void	Irc::exec_cmd(User &user) {

	std::string	str;
	size_t		len;
	int			nb_cmd;
	function_p 	command[5] = { &Irc::pass, &Irc::nick, &Irc::user_cmd, &Irc::privmsg, &Irc::join };

	str = user.getBuffer();
	if (str.find("\n", 0) == -1) { // == npos ?

		std::cout << PYELLOW << "server: request: " << str << PRESET << "\n";
		return ;
	}
	std::cout << PYELLOW << "server: request: " << str << PRESET;
	nb_cmd = is_command(str, user);
	if (user.isRegistered() == false && nb_cmd >= 4) {
		write(user.getSocket(), "User not registered\n", 20);
		write(user.getSocket(), "Usage : PASS and NICK/USER\n", 27);
	}
	else if (user.isRegistered() && (nb_cmd >= 1 && nb_cmd <= 3))
		write(user.getSocket(), "You are already registered\n", 27);	
	else 
		(this->*command[nb_cmd - 1])(user);
	// else if (is_operator())
	user.setBuffer("");
}

void	Irc::checkClientRequest(void) {

	std::list<User>::iterator	actual;
	int							readed;
	char						buf[1024];

	memset(buf, '\0', 1024);
	for (actual = _users.begin(); actual != _users.end(); ++actual) {

		memset(buf, '\0', 1024);
		readed = recv(actual->getSocket(), buf, 1023, MSG_DONTWAIT);
		if (readed == 0) {

			close(actual->getSocket());
			std::cout << PRED << "server: client n°" << actual->getSocket() - 3 \
				<< " disconnected" << PRESET << "\n";
			actual = _users.erase(actual);
			actual--;
		}
		else {
			actual->setBuffer(actual->getBuffer() + std::string(buf));
			this->exec_cmd(*actual);
		}
	}
}

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/

void	Irc::setSigintHandler(void (*handler)(int)) {

	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, 0);
}

void	Irc::run(void) {

	struct sockaddr_in	addr;
	fd_set				set;
	User				newuser;
	int					size;
	int					max;
	int					new_fd;
	int					ready_to_read;

	size = sizeof(struct sockaddr_in);
	while (1) {

		FD_ZERO(&set);
		FD_SET(this->_socket, &set);
		max = setSockets(&set);
		ready_to_read = select(max + 1, &set, NULL, NULL, NULL);//	attente d'une connection
																//	sur la socket
		if (ready_to_read < 0) {

			std::cerr << PRED << "server: select failed" << PRESET << std::endl;
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(this->_socket, &set)) {

			new_fd = accept(this->_socket, (struct sockaddr *)&addr, (socklen_t *)&size);
			if (new_fd == -1) {

				std::cerr << PRED << "server: accept failed" << PRESET << std::endl;
				exit(EXIT_FAILURE);
			}
			newuser.setSocket(new_fd);
			this->_users.push_back(newuser);
			std::cout << PYELLOW << "server: client n°" << new_fd - 3 \
				<< " connected" << PRESET << "\n";
		}
		checkClientRequest();
	}
}
