/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc_run.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 03:52:02 by parinder          #+#    #+#             */
/*   Updated: 2024/04/30 04:16:22 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

// Check if it is a command and then set the rest of the command in the buffer
// return -1 if it is not
static int	is_command(std::string buf, User &actual) {

	int			i;
	char		command[9];
	std::string	cmd[5] = {"PASS", "NICK", "USER", "PRIVMSG", "JOIN"};

	memset(command, '\0', 9);
	buf = skip_isspace(buf);
	i = 0;
	while (isalnum(buf[i])) {

		command[i] = buf[i];
		i++;
	}
	for (int j = 0; j < 5; j++) {

		if (cmd[j].compare(command) == 0) {

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
	function_p 	command[5] = { &Irc::pass, &Irc::nick, &Irc::user, &Irc::privmsg, &Irc::join };

	str = user.getBuffer();
	if (str.find("\n", 0) == -1) { // == npos ?

		std::cout << PYELLOW << "server: request: " << str << PRESET << "\n";
		return ;
	}
	std::cout << PYELLOW << "server: request: " << str << PRESET;
	nb_cmd = is_command(str, user);
	if (user.isRegistered() == false && nb_cmd >= 4)
		user.sendMsg(std::string("User not registered\n") + "Usage : PASS and NICK/USER\n");
	else if (user.isRegistered() && (nb_cmd >= 1 && nb_cmd <= 3))
		user.sendMsg("You are already registered\n");	
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
