/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luhego <luhego@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:11:49 by parinder          #+#    #+#             */
/*   Updated: 2024/07/09 18:12:30 by luhego           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT
#define BOT

#include <arpa/inet.h>
#include "header.h"
#include "Irc.hpp"

class	Bot {

private:
/*	-	-	-	-	-	private Variables	-	-	-	-	-	*/
	int			_socket;
	std::string	_pass;

	void	exec_cmd(void);

public:
/*	-	-	-	-	-	Constructors	-	-	-	-	-	*/
	Bot(const std::string ip, const std::string port, const std::string password);
/*	-	-	-	-	-	Destructors	-	-	-	-	-	*/
	~Bot(void);
/*	-	-	-	-	-	Main Functions	-	-	-	-	-	*/
	void	setSigintHandler(void (*handler)(int));
	void	run(void);
};

extern Bot	*g_BotPtr;

#endif