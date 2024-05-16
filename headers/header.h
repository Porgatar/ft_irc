/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:28:31 by parinder          #+#    #+#             */
/*   Updated: 2024/05/16 06:49:56 by maxime           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//	std::string & print redirection dependency
#include <iostream>
#include <sstream>
//	list for users & channels dependency
#include <list>
#include <vector>
//	fcntl dependency
#include <unistd.h>
#include <fcntl.h>
//	getprotobyname dependency
#include <netdb.h>
//	select dependency
#include <sys/select.h> // not needed to compile ????
//	inet_addr/socket/htons/bind/listen dependency
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//	memset dependency
#include <cstring>
//	signal handler dependency
#include <signal.h>
#include <cstdio>
//	itoa
#include <stdlib.h>

//	unknown dependency
#include <algorithm>
#include <netdb.h>

#define PRED		"\033[0;31m"
#define PYELLOW		"\033[0;33m"
#define PORANGE		"\033[0;93m"
#define PRESET		"\033[0m"

//	irc class defines
#define ERROR	101
#define WARNING	102
#define DEBUG	103
#define INFO	104

//	user class defines
#define REGISTERED	3

//	channel class is(), add() and _mode defines
#define USER_LIST		0
#define OPERATOR_LIST	1
#define INVITE_LIST		2
#define I				0
#define T				1

//	Reply Macros
//	WELCOME_RPL

std::string	skip_words(int n, const std::string &str);
    