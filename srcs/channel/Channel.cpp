/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/06 19:35:03 by mdesrose         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Channel::Channel(void) : _name("") {

	std::cout << "Channel: default constructor\n";
};

Channel::Channel(const Channel &src) {

	std::cout << "Channel: copy constructor\n";
	*this = src;
}

Channel::Channel(const std::string name, User user) : _name(name) {

	std::cout << "Channel: name/user constructor\n";
	this->addUser(user);
	this->addOperator(user);
};

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Channel::~Channel(void) {

	std::cout << "Channel: destructor\n";
};

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Channel	&Channel::operator=(const Channel &rhs) {

	std::cout << "Channel: copy operator'='\n";
	this->_name = rhs._name;
	this->_operators = rhs._operators;
	this->_users = rhs._users;
	return (*this);
}

void	Channel::setTopic(std::string name) {

	_topic = name;
}

/*	-	-	-	-	-	Getters	-	-	-	-	-	*/

std::string	Channel::getName() const {
	
	return (_name);
}

std::string	Channel::getTopic() const {
	
	return (this->_topic);
}

