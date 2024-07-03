#include "../../../headers/Irc.hpp"

void	Irc::part(User &actual) {

	std::list<Channel>::iterator chan;

	chan = getChannelIteratorByName(_args[1]);
	if (_args.size() < 2)
		return;
	else if (chan == _channels.end())
        reply(NOSUCHCHANNEL(actual, _args[1]));
    else if (chan->isIn(USER_LIST, actual.getNickname()) == false)
        reply(NOTONCHANNEL_ERR(actual, chan->getName()));
	else {
		clearUserFromChan(actual.getNickname());
		actual.sendMsg("leave channel \"" + chan->getName() + "\"");
		if (chan->getNbUser() < 1)
			_channels.erase(chan);
	}
}