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

#include "abstractspectrumbuddy.h"
#include "main.h" // just for replaceBadJidCharacters
#include "transport.h"
#include "usermanager.h"

AbstractSpectrumBuddy::AbstractSpectrumBuddy(long id) : m_id(id), m_online(false), m_subscription("ask"), m_flags(0) {
}

AbstractSpectrumBuddy::~AbstractSpectrumBuddy() {
}

void AbstractSpectrumBuddy::setId(long id) {
	m_id = id;
}

long AbstractSpectrumBuddy::getId() {
	return m_id;
}

void AbstractSpectrumBuddy::setFlags(int flags) {
	m_flags = flags;
}

int AbstractSpectrumBuddy::getFlags() {
	return m_flags;
}

std::string AbstractSpectrumBuddy::getBareJid() {
	return getSafeName() + "@" + Transport::instance()->jid();
}

std::string AbstractSpectrumBuddy::getJid() {
	return getSafeName() + "@" + Transport::instance()->jid() + "/bot";
}

void AbstractSpectrumBuddy::setOnline() {
#ifndef TESTS
	if (!m_online)
		Transport::instance()->userManager()->buddyOnline();
#endif
	m_online = true;
}

void AbstractSpectrumBuddy::setOffline() {
#ifndef TESTS
	if (m_online)
		Transport::instance()->userManager()->buddyOffline();
#endif
	m_online = false;
	m_lastPresence = "";
}

bool AbstractSpectrumBuddy::isOnline() {
	return m_online;
}

void AbstractSpectrumBuddy::setSubscription(const std::string &subscription) {
	m_subscription = subscription;
}

const std::string &AbstractSpectrumBuddy::getSubscription() {
	return m_subscription;
}

Tag *AbstractSpectrumBuddy::generatePresenceStanza(int features, bool only_new) {
	std::string alias = getAlias();
	std::string name = getSafeName();

	PurpleStatusPrimitive s;
	std::string statusMessage;
	if (!getStatus(s, statusMessage))
		return NULL;

	Tag *tag = new Tag("presence");
	tag->addAttribute("from", getJid());

	if (!statusMessage.empty())
		tag->addChild( new Tag("status", statusMessage) );

	switch(s) {
		case PURPLE_STATUS_AVAILABLE: {
			break;
		}
		case PURPLE_STATUS_AWAY: {
			tag->addChild( new Tag("show", "away" ) );
			break;
		}
		case PURPLE_STATUS_UNAVAILABLE: {
			tag->addChild( new Tag("show", "dnd" ) );
			break;
		}
		case PURPLE_STATUS_EXTENDED_AWAY: {
			tag->addChild( new Tag("show", "xa" ) );
			break;
		}
		case PURPLE_STATUS_OFFLINE: {
			tag->addAttribute( "type", "unavailable" );
			break;
		}
		default:
			break;
	}

	if (s != PURPLE_STATUS_OFFLINE) {
		// caps
		Tag *c = new Tag("c");
		c->addAttribute("xmlns", "http://jabber.org/protocol/caps");
		c->addAttribute("hash", "sha-1");
		c->addAttribute("node", "http://spectrum.im/transport");
		c->addAttribute("ver", Transport::instance()->hash());
		tag->addChild(c);

		if (features & TRANSPORT_FEATURE_AVATARS) {
			// vcard-temp:x:update
			Tag *x = new Tag("x");
			x->addAttribute("xmlns","vcard-temp:x:update");
			x->addChild( new Tag("photo", getIconHash()) );
			tag->addChild(x);
		}
	}

	if (only_new) {
		if (m_lastPresence == tag->xml()) {
			delete tag;
			return NULL;
		}
		m_lastPresence = tag->xml();
	}

	return tag;
}
