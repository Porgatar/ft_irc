/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:10:03 by parinder          #+#    #+#             */
/*   Updated: 2024/04/29 17:32:30 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "header.h"
#include "User.hpp"
#include "Channel.hpp"
#include "Utils.h"

class Irc {

private:

/*	-	-	-	-	-	private Variables	-	-	-	-	*/
	int					_socket;
	std::string			_password;
	std::list<User>		_users;
	std::list<Channel>	_channels;
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(void);
/*	-	-	-	-	-	Private Functions	-	-	-	-	*/
	int		setSockets(fd_set *set);
	void	checkClientRequest(void);
	void 	exec_cmd(User &user);
	void	addUser(int socket);
	bool	check_existing_channel(std::string channels_name, User &user);
/*	-	-	-	-	-	Command Functions	-	-	-	-	*/
	void 	cap(User &user);
	void	pass(User &actual);
	void	user_cmd(User &actual);
	void	nick(User &actual);
	void	join(User &actual);
	void	privmsg(User &actual);
	void 	launch_cmd(int command_number, User &actual);

public:

/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Irc(const Irc &src);
	Irc(const std::string port, const std::string password);
/*	-	-	-	-	-	Destructors	-	-	-	-	-	-	*/
	~Irc(void);
/*	-	-	-	-	-	Operators	-	-	-	-	-	-	*/
	Irc			&operator=(const Irc &rhs);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void	setSigintHandler(void (*handler)(int));
	void	run(void);
};

extern Irc	*g_IrcPtr;

typedef void (Irc::*function_p)(User &);
