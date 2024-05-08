/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/08 15:47:49 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Channel::Channel(void) : _name("") {

	for (int i = 0; i < 5; i++)
		this->_mode[i] = false;
};

Channel::Channel(const Channel &src) : \
	_name(src._name), _operators(src._operators), _users(src._users) {

	for (int i = 0; i < 5; i++)
		this->_mode[i] = src._mode[i];
}

Channel::Channel(const std::string name, User user) : _name(name) {

	for (int i = 0; i < 5; i++)
		this->_mode[i] = false;
	this->addUser(user);
	this->addOperator(user);
};

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Channel::~Channel(void) {};

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Channel	&Channel::operator=(const Channel &rhs) {

	this->_name = rhs._name;
	for (int i = 0; i < 5; i++)
		this->_mode[i] = rhs._mode[i];
	this->_operators = rhs._operators;
	this->_users = rhs._users;
	return (*this);
}

void	Channel::setTopic(std::string name) {

	_topic = name;
}

/*	-	-	-	-	-	Getters	-	-	-	-	-	*/

const std::string	&Channel::getTopic() const {
	
	return (this->_topic);
}

const std::string	&Channel::getName(void) const {return (_name);}

const bool			&Channel::getMode(const int &mode) const {return (this->_mode[mode]);}

/*	-	-	-	-	-	Setters	-	-	-	-	-	*/

void	Channel::setMode(const int &mode, const bool &state) {this->_mode[mode] = state;}
