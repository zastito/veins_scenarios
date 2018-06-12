//
// Copyright (C) 2006-2012 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef VEINS_MOBILITY_BASE_TRACI_BASETRACIMOBILITY_H
#define VEINS_MOBILITY_BASE_TRACI_BASETRACIMOBILITY_H

#define TRACI_SIGNAL_PARKING_CHANGE_NAME "parkingStateChanged"

#include <string>
#include <fstream>
#include <list>
#include <stdexcept>

#include "veins/base/modules/BaseMobility.h"
#include "veins/base/utils/FindModule.h"
#include "veins/modules/mobility/traci/TraCIScenarioManager.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

/**
 * @brief
 * Used in modules created by the TraCIScenarioManager.
 *
 * This module relies on the TraCIScenarioManager for state updates
 * and can not be used on its own.
 *
 * See the Veins website <a href="http://veins.car2x.org/"> for a tutorial, documentation, and publications </a>.
 *
 * @author Christoph Sommer, David Eckhoff, Luca Bedogni, Bastian Halmos, Stefan Joerer
 *
 * @see TraCIScenarioManager
 * @see TraCIScenarioManagerLaunchd
 *
 * @ingroup mobility
 */
namespace Veins {
class BaseTraCIMobility : public BaseMobility
{
	public:

		BaseTraCIMobility() : BaseMobility(), manager(0), commandInterface(0) {}

		virtual void initialize(int);

        virtual TraCIScenarioManager* getManager() const {
            if (!manager) manager = TraCIScenarioManagerAccess().get();
            return manager;
        }

		virtual TraCICommandInterface* getCommandInterface() const {
			if (!commandInterface) commandInterface = getManager()->getCommandInterface();
			return commandInterface;
		}


	protected:
		bool debug; /**< whether to emit debug messages */

		mutable TraCIScenarioManager* manager;
		mutable TraCICommandInterface* commandInterface;
};
}

namespace Veins {
class BaseTraCIMobilityAccess
{
	public:
		BaseTraCIMobility* get(cModule* host) {
			BaseTraCIMobility* traci = FindModule<BaseTraCIMobility*>::findSubModule(host);
			ASSERT(traci);
			return traci;
		};
};
}

#endif

