/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/18 15:17:31 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "User.hpp"


#define NB_CLIENTS 5

class Irc {

private:

	Irc(void);

	int			_port;
	int			_socket;
	std::string	_password;
	User		_user[NB_CLIENTS];
public:

	Irc(const Irc &src);
	Irc(const std::string port, const std::string password);
	~Irc(void);

	Irc	&operator=(const Irc &rhs);

	int			getsocket() const;
	std::string getpassword() const;
	int			getport() const;

	int			create_server();
	void		loop_for_connection();
	int			set_sockets(fd_set *set);
};
