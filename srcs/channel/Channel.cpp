/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/05/16 06:50:00 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Channel.hpp"

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/

Channel::Channel(void) : _name(""), _key(""), _topic(""), _userLimit(0) {

	for (int i = 0; i < 2; i++)
		this->_modes[i] = false;
};

Channel::Channel(const Channel &src) : \
	_name(src._name), _key(src._key) , _topic(src._topic), _userLimit(src._userLimit) {

	for (int i = 0; i < 2; i++)
		this->_modes[i] = src._modes[i];
	this->_users[USER_LIST] = src._users[USER_LIST];
	this->_users[OPERATOR_LIST] = src._users[OPERATOR_LIST];
	this->_users[INVITE_LIST] = src._users[INVITE_LIST];
}

Channel::Channel(const std::string &name, const User &user) : \
	_name(name), _key("") , _topic(""), _userLimit(0) {

	for (int i = 0; i < 2; i++)
		this->_modes[i] = false;
	this->addUserTo(USER_LIST, user);
	this->addUserTo(OPERATOR_LIST, user);
};

/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/

Channel::~Channel(void) {};

/*	-	-	-	-	-	Operators	-	-	-	-	-	*/

Channel	&Channel::operator=(const Channel &rhs) {

	this->_name = rhs._name;
	this->_key = rhs._key;
	this->_topic = rhs._topic;
	for (int i = 0; i < 2; i++)
		this->_modes[i] = rhs._modes[i];
	this->_users[USER_LIST] = rhs._users[USER_LIST];
	this->_users[OPERATOR_LIST] = rhs._users[OPERATOR_LIST];
	this->_users[INVITE_LIST] = rhs._users[INVITE_LIST];
	this->_userLimit = rhs._userLimit;
	return (*this);
}

/*	-	-	-	-	-	Getters	-	-	-	-	-	*/

const std::string	&Channel::getName(void) const {return (this->_name);}

const std::string	&Channel::getKey(void) const {return (this->_key);}

const std::string	&Channel::getTopic() const {return (this->_topic);}

bool	Channel::getMode(const int &mode) const {

	if (mode >= 0 && mode <= 1)
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

const size_t	&Channel::getUserLimit(void) const {return (this->_userLimit);}

/*	-	-	-	-	-	Setters	-	-	-	-	-	*/

void	Channel::setKey(const std::string &key) {this->_key = key;}

void	Channel::setTopic(const std::string &topic) {this->_topic = topic;}

void	Channel::setMode(const int &mode, const bool &state) {

	if (mode >= 0 && mode <= 1)
		this->_modes[mode] = state;
}

void	Channel::addUserTo(const int &list, const User &user) {

	if (!this->getUserByNameFrom(list, user.getNickname()) && list >= 0 && list <= 2)
		this->_users[list].push_back(user);
}

void	Channel::setUserLimit(const size_t &userLimit) {this->_userLimit = userLimit;}
