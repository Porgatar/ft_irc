/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc_log.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parinder <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 21:21:20 by parinder          #+#    #+#             */
/*   Updated: 2024/05/08 17:31:11 by parinder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Irc.hpp"

void	Irc::log(int log, const std::string &str) {

	if (log == ERROR)
		std::cerr << PRED << str << PRESET << std::endl;
	else if (log == WARNING)
		std::cout << PORANGE << str << PRESET << "\n";
	else if (log == INFO)
		std::cout << PYELLOW << str << PRESET << "\n";
}
