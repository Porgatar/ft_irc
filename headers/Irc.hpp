/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/24 22:24:27 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sys/select.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>  
#include <sys/types.h> 
#include <sys/socket.h>  
#include <string.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <list>
#include <algorithm>

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
public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(const Irc &src);
	Irc(const std::string port, const std::string password);

/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~Irc(void);

/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	Irc			&operator=(const Irc &rhs);

/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void		loop_for_connection(void);
	int			set_sockets(fd_set *set);
	void		is_writing(void);
	void		init_new_user(int socket);

	void 		exec_cmd(User &user);
//	void 		exec_command(int command_number, std::list<User>::iterator actual);

/*	-	-	-	-	-	Command Functions	-	-	-	-	*/
	void		join(std::list<User>::iterator actual);
	void		nick(std::list<User>::iterator actual);
	void		user(std::list<User>::iterator actual);
	void		privmsg(std::list<User>::iterator actual);
};
