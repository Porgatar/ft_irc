/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/20 01:47:48 by maxime           ###   ########.fr       */
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
#include "Channel.hpp"
#include <vector>
#include <algorithm>

#define NB_CLIENTS 5

class Irc {

private:

	Irc(void);
	Irc(const Irc &src);

	int			_socket;
	std::string	_password;
	std::vector<User> _user;
	Channel		*_channel;	// chained class Channel
public:

	Irc(const std::string port, const std::string password);
	~Irc(void);

	Irc	&operator=(const Irc &rhs);

	int			getsocket() const;
	std::string getpassword() const;

	int			create_server();
	void		loop_for_connection();
	int			set_sockets(fd_set *set);
	void		send_message(fd_set *set);
	void		init_new_user(int socket);
};
