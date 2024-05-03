/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc_log.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:21:20 by parinder          #+#    #+#             */
/*   Updated: 2024/05/03 23:03:04 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

void	Irc::log(int log, const std::string &str) {

	if (log == ERROR)
		std::cerr << PRED << str << PRESET << std::endl;
	else if (log == WARNING || log == INFO)
		std::cout << PYELLOW << str << PRESET << "\n";
}
