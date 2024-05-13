/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/13 14:57:59 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Channel::Channel(void) : _name(""), _topic("") {

	for (int i = 0; i < 5; i++)
		this->_modes[i] = false;
};

Channel::Channel(const Channel &src) : \
	_name(src._name), _topic(src._topic) {

	for (int i = 0; i < 5; i++)
		this->_modes[i] = src._modes[i];
	this->_users[USER] = src._users[USER];
	this->_users[OPERATOR] = src._users[OPERATOR];
	this->_users[INVITE] = src._users[INVITE];
}

Channel::Channel(const std::string &name, const User &user) : _name(name), _topic("") {

	for (int i = 0; i < 5; i++)
		this->_modes[i] = false;
	this->addTo(USER, user);
	this->addTo(OPERATOR, user);
};

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Channel::~Channel(void) {};

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Channel	&Channel::operator=(const Channel &rhs) {

	this->_name = rhs._name;
	this->_topic = rhs._topic;
	for (int i = 0; i < 5; i++)
		this->_modes[i] = rhs._modes[i];
	this->_users[USER] = rhs._users[USER];
	this->_users[OPERATOR] = rhs._users[OPERATOR];
	this->_users[INVITE] = rhs._users[INVITE];
	return (*this);
}

/*	-	-	-	-	-	Getters	-	-	-	-	-	*/

const std::string	&Channel::getName(void) const {return (this->_name);}

const std::string	&Channel::getTopic() const {return (this->_topic);}

const bool	&Channel::getMode(const int &mode) const {return (this->_modes[mode]);}

bool	Channel::isIn(const int &list, const std::string &nick) {

	std::list<User>::iterator it;

	for (it = this->_users[list].begin(); it != this->_users[list].end(); it++)
		if (nick == it->getNickname())
			return (true);
	return (false);
}

/*	-	-	-	-	-	Setters	-	-	-	-	-	*/

void	Channel::setTopic(const std::string &topic) {this->_topic = topic;}

void	Channel::setMode(const int &mode, const bool &state) {this->_modes[mode] = state;}

void	Channel::addTo(const int &list, const User &user) {this->_users[list].push_back(user);}
