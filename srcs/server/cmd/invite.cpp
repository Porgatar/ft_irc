#include "../../../headers/Irc.hpp"

void    Irc::invite(User &actual)
{
    std::list<User>::iterator it;
    std::list<Channel>::iterator chan;

    chan = getChannelIteratorByName(this->_args[2]);
    if (this->_args.size() < 3)
        this->reply(NEEDMOREPARAMS(actual, "INVITE"));
    else if (checkExistingUser(this->_args[1]) == false)
        this->reply(NOSUCHNICK(actual, this->_args[1]));
    else if (chan == this->_channels.end())
        this->reply(NOSUCHCHANNEL(actual, this->_args[2]));
    else if (chan->isIn(USER_LIST, actual.getNickname()) == false)
        this->reply(NOTONCHANNEL(actual, chan->getName()));
    else if (chan->isIn(OPERATOR_LIST, actual.getNickname()) == false)
        this->reply(CHANOPRIVSNEEDED(actual, chan->getName()));
    else if (chan->isIn(USER_LIST, this->_args[1]) == true)
        this->reply(USERONCHANNEL(actual, this->_args[1], chan->getName()));
    else {
        for (it = _users.begin(); it != _users.end(); it++) {
            if (this->_args[1] == it->getNickname())
                break;
        }
        chan->addUserTo(INVITE_LIST, *it);
        actual.sendMsg(it->getNickname() + " has been invited to channel : " + _args[2]);
    }
}
