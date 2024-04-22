/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/22 05:27:03 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Channel.hpp"

Channel::Channel(void) : _name("") {

	std::cout << "Channel: default constructor\n";
};

Channel::Channel(const Channel &src) {

	std::cout << "Channel: copy constructor\n";
	*this = src;
}

Channel::Channel(const std::string name, User *user) : _name(name) {

	std::cout << "Channel: name/user constructor\n";
	this->add_user(user);
	this->add_operator(user);
};

Channel::~Channel(void) {

	std::cout << "Channel: destructor\n";
};

Channel	&Channel::operator=(const Channel &rhs) {

	std::cout << "Channel: copy operator'='\n";
	this->_name = rhs._name;
	this->_operators = rhs._operators;
	this->_users = rhs._users;
	return (*this);
}

void	Channel::send_group_msg(std::string msg) {

	std::cout << "Channel: group message: " << msg << "\n";
	//send msg to all users.
}

void	Channel::add_user(User *user) {

	std::cout << "Channel: adding user\n";
	this->_users.push_front(user);
}

void	Channel::add_operator(User *user) {

	std::cout << "Channel: adding operator\n";
	this->_operators.push_front(user);
}
