/**
 * XMPP - libpurple transport
 *
 * Copyright (C) 2009, Jan Kaluza <hanzz@soc.pidgin.im>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#include "groupwise.h"

GroupWiseProtocol::GroupWiseProtocol() {
	m_transportFeatures.push_back("jabber:iq:register");
	m_transportFeatures.push_back("jabber:iq:gateway");
	m_transportFeatures.push_back("http://jabber.org/protocol/disco#info");
	m_transportFeatures.push_back("http://jabber.org/protocol/caps");
	m_transportFeatures.push_back("http://jabber.org/protocol/chatstates");
// 	m_transportFeatures.push_back("http://jabber.org/protocol/activity+notify");
	m_transportFeatures.push_back("http://jabber.org/protocol/commands");

	m_buddyFeatures.push_back("http://jabber.org/protocol/disco#info");
	m_buddyFeatures.push_back("http://jabber.org/protocol/disco#items");
	m_buddyFeatures.push_back("http://jabber.org/protocol/caps");
	m_buddyFeatures.push_back("http://jabber.org/protocol/chatstates");
	m_buddyFeatures.push_back("http://jabber.org/protocol/commands");

	m_buddyFeatures.push_back("http://jabber.org/protocol/si");
}

GroupWiseProtocol::~GroupWiseProtocol() {}

std::list<std::string> GroupWiseProtocol::transportFeatures(){
	return m_transportFeatures;
}

std::list<std::string> GroupWiseProtocol::buddyFeatures(){
	return m_buddyFeatures;
}

std::string GroupWiseProtocol::text(const std::string &key) {
	if (key == "instructions")
		return _("Please use user@server:port");
	else if (key == "username")
		return _("user@server:port");
	return "not defined";
}

void GroupWiseProtocol::onPurpleAccountCreated(PurpleAccount *account) {

        AbstractUser *user = (AbstractUser *) account->ui_data;
        std::vector <std::string> u = split(user->username(), '@');
        purple_account_set_username(account, (const char*) u.front().c_str());
        std::vector <std::string> s = split(u.back(), ':'); 
        purple_account_set_string(account, "server", s.front().c_str());
        purple_account_set_int(account, "port", atoi(s.back().c_str()));  
}

SPECTRUM_PROTOCOL(groupwise, GroupWiseProtocol)
