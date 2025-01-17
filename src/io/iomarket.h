/**
 * The Forgotten Server - a free and open-source MMORPG server emulator
 * Copyright (C) 2019  Mark Samman <mark.samman@gmail.com>
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
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef SRC_IO_IOMARKET_H_
#define SRC_IO_IOMARKET_H_

#include "database/database.h"
#include "declarations.hpp"

class IOMarket
{
	public:
		static IOMarket& getInstance() {
			static IOMarket instance;
			return instance;
		}

		static MarketOfferList getActiveOffers(MarketAction_t action, uint16_t itemId, uint16_t tier);
		static MarketOfferList getOwnOffers(MarketAction_t action, uint32_t playerId);
		static HistoryMarketOfferList getOwnHistory(MarketAction_t action, uint32_t playerId);

		static void processExpiredOffers(DBResult_ptr result, bool);
		static void checkExpiredOffers();

		static uint32_t getPlayerOfferCount(uint32_t playerId);
		static MarketOfferEx getOfferByCounter(uint32_t timestamp, uint16_t counter);

		static void createOffer(uint32_t playerId, MarketAction_t action, uint32_t itemId, uint16_t amount, uint32_t price, uint16_t tier, bool anonymous);
		static void acceptOffer(uint32_t offerId, uint16_t amount);
		static void deleteOffer(uint32_t offerId);

		static void appendHistory(uint32_t playerId, MarketAction_t type, uint16_t itemId, uint16_t amount, uint32_t price, time_t timestamp, uint16_t tier, MarketOfferState_t state);
		static bool moveOfferToHistory(uint32_t offerId, MarketOfferState_t state);

		void updateStatistics();

		MarketStatistics* getPurchaseStatistics(uint16_t itemId, uint16_t tier);
		MarketStatistics* getSaleStatistics(uint16_t itemId, uint16_t tier);

	private:
		IOMarket() = default;

		//std::map<uint16_t, std::map<MarketStatistics, uint16_t>> purchaseStatistics;
		//std::map<uint16_t, std::map<MarketStatistics, uint16_t>> saleStatistics;
		std::map<uint16_t, MarketStatistics> purchaseStatistics;
		std::map<uint16_t, MarketStatistics> saleStatistics;
};

#endif  // SRC_IO_IOMARKET_H_
