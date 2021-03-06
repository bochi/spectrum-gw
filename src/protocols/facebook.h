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

#ifndef _HI_FACEBOOK_PROTOCOL_H
#define _HI_FACEBOOK_PROTOCOL_H

#include "abstractprotocol.h"

extern Localization localization;

class FacebookProtocol : AbstractProtocol
{
	public:
		FacebookProtocol();
		~FacebookProtocol();
		const std::string gatewayIdentity() { return "facebook"; }
		const std::string protocol() { return "prpl-bigbrownchunx-facebookim"; }
		bool isValidUsername(const std::string &username);
		std::list<std::string> transportFeatures();
		std::list<std::string> buddyFeatures();
		std::string text(const std::string &key);
		Tag *getVCardTag(AbstractUser *user, GList *vcardEntries);
		bool isMUC(AbstractUser *user, const std::string &jid) { return false; }
		const std::string notifyUsername() { return "info"; }
		const std::string userSearchAction() { return "Search for buddies..."; }

		const std::string userSearchColumn() { return "ID"; }

	private:
		std::list<std::string> m_transportFeatures;
		std::list<std::string> m_buddyFeatures;

};

#endif

