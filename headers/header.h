/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxime <maxime@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:28:31 by parinder          #+#    #+#             */
/*   Updated: 2024/05/02 14:18:40 by maxime           ###   ########.fr       */
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

//	unknown dependency
#include <algorithm>
#include <netdb.h>

#define PRED		"\033[0;31m"
#define PYELLOW		"\033[0;33m"
#define PRESET		"\033[0m"

#define REGISTERED	3
