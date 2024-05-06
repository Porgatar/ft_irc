/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc_run.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:52:02 by parinder          #+#    #+#             */
/*   Updated: 2024/05/06 19:19:45 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

std::vector<std::string>	split_space(std::string str) {

    std::vector<std::string>	res;
	std::istringstream			iss(str);
	std::string					buff;

	while (iss >> buff)
		res.push_back(buff);
	return (res);
}

static int	is_command(const std::string &buf) {

	std::string	cmd[7] = {"CAP", "PASS", "USER", "NICK", "PRIVMSG", "JOIN", "KICK"};
	std::string	command;

	for (int i = 0; i < 7; i++) {

		if (cmd[i].compare(buf) == 0)
			return (i);
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
	if (!len || len == std::string::npos)
		return ;
	tmp = str.substr(len + 1, str.length() - len);
	user.setBuffer(tmp);
	str = str.substr(0, len);
	user.setMessage(str);
	this->log(INFO, std::string("server: request: ") + user.getStringId() + ": " + str);
	this->_args = split_space(str);
	nb_cmd = is_command(this->_args[0]);
	if (nb_cmd == -1) {

		user.sendMsg(this->_args[0] + " :Unknown command");
		this->log(WARNING, std::string("server: reply: ") + user.getStringId() + \
			": " + this->_args[0] + " :Unknown command");
	}
	else if (!user.isRegistered() && nb_cmd >= 4) {

		user.sendMsg(" :You have not registered");
		this->log(WARNING, std::string("server: reply: ") + user.getStringId() + \
			" :You have not registered");
	}
	else if (user.isRegistered() && (nb_cmd >= 0 && nb_cmd <= 3)) {

		user.sendMsg(" :You may not reregister");
		this->log(WARNING, std::string("server: reply: ") + user.getStringId() + \
			" :You may not reregister");
	}
	else
		(this->*command[nb_cmd])(user);
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
			this->log(INFO, std::string("server: info: ") + actual->getStringId() + \
				": disconnected");
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
			this->log(INFO, std::string("server: info: ") + newuser.getStringId() + ": connected");
		}
		else
			this->checkClientRequest();
	}
}
