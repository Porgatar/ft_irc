/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/25 20:26:32 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"
#include "Channel.hpp"

class Irc {

private:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(void);
/*	-	-	-	-	-	Member Variables	-	-	-	-	*/
	int					_socket;
	std::string			_password;
	std::list<User>		_users;
	std::list<Channel>	_channels;
/*	-	-	-	-	-	Private Functions	-	-	-	-	*/
	int		set_sockets(fd_set *set);
	void	checkClientRequest(void);
	void 	exec_cmd(User &user);
	void	addUser(int socket);
/*	-	-	-	-	-	Command Functions	-	-	-	-	*/
	void 	registerUser(User &user);
	void	user(std::list<User>::iterator actual);
	void	nick(std::list<User>::iterator actual);
	void	join(std::list<User>::iterator actual);
	void	privmsg(std::list<User>::iterator actual);
public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(const Irc &src);
	Irc(const std::string port, const std::string password);
/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~Irc(void);
/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	Irc			&operator=(const Irc &rhs);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void	run(void);
};
