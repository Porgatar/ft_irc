/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc_run.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:52:02 by parinder          #+#    #+#             */
/*   Updated: 2024/05/03 23:01:33 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

static std::string	getWord(std::string str, int n) {

	std::istringstream	iss(str);

	while (n-- > 0 && (iss >> str));
	return (str);
}

// Check if it is a command and then set the rest of the command in the buffer
// return -1 if it is not
static int	is_command(std::string &buf, User &actual) {

	std::string	cmd[7] = {"CAP", "PASS", "USER", "NICK", "PRIVMSG", "JOIN", "KICK"};
	std::string command;
	int			i;

	buf = skip_isspace(buf);
	for (int j = 0; j < 7; j++) {

		if (cmd[j].compare(buf) == 0)
			return (j + 1);
	}
	return (-1);
}


void	Irc::exec_cmd(User &user) {

	std::string	str;
	std::string	tmp;
	size_t		len;
	int			nb_cmd;
	function_p 	command[7] = {	&Irc::cap, &Irc::pass, &Irc::user, &Irc::nick, \
								&Irc::privmsg, &Irc::join, &Irc::kick};

	str = user.getBuffer();
	len = str.find("\n", 0);
	if (len == std::string::npos)
		return ;
	this->log(INFO, std::string("server: request: ") + str);
	tmp = str.substr(len + 1, str.length() - len);
	user.setBuffer(tmp);
	str = str.substr(0, len);
	this->_args = split_space(str);
	nb_cmd = is_command(this->_args[0], user);
	if (nb_cmd == -1) {

		user.sendMsg(this->_args[0] + " :Unknown command");
		this->log(WARNING, std::to_string(user.getSocket() - 3) + " " + this->_args[0] + \
																" :Unknown command");
	}
	else if (!user.isRegistered() && nb_cmd > 4) {

		user.sendMsg(" :You have not registered");
		this->log(WARNING, std::to_string(user.getSocket() - 3) + " :You have not registered");
	}
	else if (user.isRegistered() && (nb_cmd > 0 && nb_cmd < 5)) {

		user.sendMsg(" :You may not reregister");
		this->log(WARNING, std::to_string(user.getSocket() - 3) + " :You may not reregister");
	}
	else
		(this->*command[nb_cmd - 1])(user);
	// else if (is_operator())
	this->exec_cmd(user);
}

void	Irc::checkClientRequest(void) {

	std::list<User>::iterator	actual;
	int							readed;
	char						buf[1024];

	for (actual = _users.begin(); actual != _users.end(); ++actual) {

		memset(buf, '\0', 1024);
		readed = recv(actual->getSocket(), buf, 1023, MSG_DONTWAIT);
		if (readed == 0) {

			close(actual->getSocket());
			this->log(INFO, std::string("server: client n°") + \
				std::to_string(actual->getSocket() - 3) + " disconnected");
			actual = _users.erase(actual);
			actual--;
		}
		else {

			actual->setBuffer(actual->getBuffer() + std::string(buf));
			this->exec_cmd(*actual);
		}
	}
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

			this->log(ERROR, "server: select failed");
			exit(EXIT_FAILURE);
		}
		if (FD_ISSET(this->_socket, &set)) {

			new_fd = accept(this->_socket, (struct sockaddr *)&addr, (socklen_t *)&size);
			if (new_fd == -1) {

				this->log(ERROR, "server: accept failed");
				exit(EXIT_FAILURE);
			}
			newuser.setSocket(new_fd);
			this->_users.push_back(newuser);
			this->log(INFO, std::string("server: client n°") + std::to_string(new_fd - 3) + \
																			" connected");
		}
		else
			this->checkClientRequest();
	}
}
