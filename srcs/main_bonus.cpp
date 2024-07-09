#include "../headers/header.h"
#include "../headers/Bot.hpp"

//catching bot global pointer to destroy class instance
static void	ft_exit(int sig)
{
	std::cout << PRED << "bot shutdown..." << PRESET << std::endl;
	g_BotPtr->~Bot();
	exit(sig);
}

int main(int ac, char **av)
{
	if (ac == 4)
	{
		Bot	bot(av[1], av[2], av[3]);
		bot.setSigintHandler(ft_exit);
		bot.run();
		return (0);
	}
	std::cerr << PRED << "Error\ninvalid format\n" \
		<< "usage: ./bot <ip> <port> <password>"  << PRESET << std::endl;
	return (-1);
}