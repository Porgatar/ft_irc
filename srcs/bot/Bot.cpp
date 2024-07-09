/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <luhego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:10:50 by parinder          #+#    #+#             */
/*   Updated: 2024/07/09 18:46:51 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Bot.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
Bot::Bot(const std::string ip, const std::string port, const std::string password) \
	 :_pass(password) {
	struct sockaddr_in serv_addr;

	this->_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socket < 0) {

        std::cerr << "Socket creation error" << std::endl;
        exit(0);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(port.c_str()));
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {

        std::cerr << "Invalid address/ Address not supported" << std::endl;
		this->~Bot();
        exit(0);
    }
    if (connect(_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {

        std::cerr << "Connection Failed" << std::endl;
		this->~Bot();
        exit(0);
    }
	std::string pass = "PASS " + _pass + "\n" + "NICK Boty\nUSER \n";
	send(this->_socket, pass.c_str(), pass.size(), 0);
}

Bot::~Bot(void) {

	close(this->_socket);
};

void	Bot::setSigintHandler(void (*handler)(int)) {

	struct sigaction	sa;

	g_BotPtr = this;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handler;
	sigaction(SIGINT, &sa, 0);
}

static std::vector<std::string>	split_space(std::string str) {

    std::vector<std::string>	res;
	std::istringstream			iss(str);
	std::string					buff;

	while (iss >> buff)
		res.push_back(buff);
	return (res);
}

void	Bot::run(void)
{
	char	buff[1024] = {0};

	int	readed = recv(this->_socket, buff, 1023, 0);
	buff[readed] = 0;
	if (!readed || std::string(buff) != ": 001 Boty :Welcome to The Internet Relay Chat world, Boty\r\n") {

		std::cerr << "authentication failed..." << std::endl;
		return ;
	}
	while (1)
	{
		int	readed = recv(this->_socket, buff, 1023, 0);

		buff[readed] = 0;
		if (!readed) {

			std::cerr << "host closed connection..." << std::endl;
			return ;
		}
		std::vector<std::string>	vector = split_space(buff);

		if (vector[0][0] == ':')
			vector[0] = vector[0].substr(1);
		std::cout << vector[0] << std::endl;
		if (vector[3] == "!intra") {

			std::string reply;

			reply = "PRIVMSG " + vector[0] + " https://profile.intra.42.fr/\n";
			send(this->_socket, reply.c_str(), reply.size(), 0);
		}
	}
	return ;
}

Bot*	g_BotPtr;
