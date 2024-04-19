/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:49:44 by parinder          #+#    #+#             */
/*   Updated: 2024/04/18 00:41:14 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/User.hpp"
#include "../headers/Channel.hpp"

Channel::Channel(void) : _name(""), _users(0), _operators(0), next(0) {};

Channel::Channel(const Channel &src) {

	*this = src;
}

Channel::~Channel(void){};

Channel	&Channel::operator=(const Channel &rhs) {

	this->_name = rhs._name;
	return (*this);
}
