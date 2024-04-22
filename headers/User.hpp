/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:49:49 by maxime            #+#    #+#             */
/*   Updated: 2024/04/22 13:56:49 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

class User {

private:

	int			_isconnected;
	int			_socket;
	std::string	_username;
	std::string	_nickname;
	std::string	_buffer;
public:

	User(int socket, std::string username, std::string nickname);
	User(const User &src);
	~User(void);

	User	&operator=(const User &rhs);

	int			getsocket() const;
	void		setsocket(int fd);
	void		setbuffer(char *buf);
	bool		isconnect();
	std::string	getbuffer() const;


};
