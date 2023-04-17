#include "User.h"
#include <iostream>

void User::viewsent()
{
	if (sent.empty())
	{
		cout << "You haven't sent any messages yet.";
	}
	else
	{
		for(auto msg:sent)
		{
			msg.viewAsSent();
		}
	}
}

void User::viewreceived()
{
	if (inbox.empty())
	{
		cout << "Your inbox is empty.";
	}
	else
	{
		for (auto msg : sent)
		{
			msg.viewAsReceived();
		}
	}
}

