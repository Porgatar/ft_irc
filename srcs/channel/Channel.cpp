/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdesrose <mdesrose@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/14 16:31:50 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Channel::Channel(void) : _name(""), _topic("") {

	for (int i = 0; i < 4; i++)
		this->_modes[i] = false;
};

Channel::Channel(const Channel &src) : \
	_name(src._name), _topic(src._topic) {

	for (int i = 0; i < 4; i++)
		this->_modes[i] = src._modes[i];
	this->_users[USER_LIST] = src._users[USER_LIST];
	this->_users[OPERATOR_LIST] = src._users[OPERATOR_LIST];
	this->_users[INVITE_LIST] = src._users[INVITE_LIST];
}

Channel::Channel(const std::string &name, const User &user) : _name(name), _topic("") {

	for (int i = 0; i < 4; i++)
		this->_modes[i] = false;
	this->addUserTo(USER_LIST, user);
	this->addUserTo(OPERATOR_LIST, user);
};

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Channel::~Channel(void) {};

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Channel	&Channel::operator=(const Channel &rhs) {

	this->_name = rhs._name;
	this->_topic = rhs._topic;
	for (int i = 0; i < 4; i++)
		this->_modes[i] = rhs._modes[i];
	this->_users[USER_LIST] = rhs._users[USER_LIST];
	this->_users[OPERATOR_LIST] = rhs._users[OPERATOR_LIST];
	this->_users[INVITE_LIST] = rhs._users[INVITE_LIST];
	return (*this);
}

/*	-	-	-	-	-	Getters	-	-	-	-	-	*/

const std::string	&Channel::getName(void) const {return (this->_name);}

const std::string	&Channel::getTopic() const {return (this->_topic);}

bool	Channel::getMode(const int &mode) const {

	if (mode >= 0 && mode <= 3)
		return (this->_modes[mode]);
	return (false);
}

User	*Channel::getUserByNameFrom(const int &list, const std::string &nick) {

	std::list<User>::iterator it;

	if (list >= 0 && list <= 2)
		for (it = this->_users[list].begin(); it != this->_users[list].end(); it++)
			if (nick == it->getNickname())
				return (&*it);
	return (0);
}

/*	-	-	-	-	-	Setters	-	-	-	-	-	*/

void	Channel::setTopic(const std::string &topic) {this->_topic = topic;}

void	Channel::setMode(const int &mode, const bool &state) {

	if (mode >= 0 && mode <= 3)
		this->_modes[mode] = state;
}

void	Channel::addUserTo(const int &list, const User &user) {

	if (!this->getUserByNameFrom(list, user.getNickname()) && list >= 0 && list <= 2)
		this->_users[list].push_back(user);
}
