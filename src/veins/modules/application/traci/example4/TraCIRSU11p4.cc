//
// Copyright (C) 2016 David Eckhoff <david.eckhoff@fau.de>
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

#include "veins/modules/mobility/traci/TraCICommandInterface.h"

#include <BaseTraCIMobility.h>
#include <TraCIRSU11p4.h>

using Veins::BaseTraCIMobility;
using Veins::BaseTraCIMobilityAccess;

Define_Module(TraCIRSU11p4);

BaseTraCIMobility *mobility1;
TraCICommandInterface *traci1;

void TraCIRSU11p4::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);

    if (stage == 0) {
        sentMessage = false;
    }
}

void TraCIRSU11p4::onWSA(WaveServiceAdvertisment* wsa) {
    //if this RSU receives a WSA for service 42, it will tune to the chan
    if (wsa->getPsid() == 42) {
        mac->changeServiceChannel(wsa->getTargetChannel());
    }
}

void TraCIRSU11p4::onWSM(WaveShortMessage* wsm) {
    //this rsu repeats the received traffic update in 2 seconds plus some random delay
    wsm->setSenderAddress(myId);
    sendDelayedDown(wsm->dup(), 2 + uniform(0.01,0.2));
}

void TraCIRSU11p4::onBSM(BasicSafetyMessage* bsm) {
    if (sentMessage == false) {

        mobility1 = BaseTraCIMobilityAccess().get(getParentModule());
        traci1 = mobility1->getCommandInterface();

        traci1->trafficlight("1093385867").setProgram("myProgram");
        traci1->trafficlight("1093385867").setPhaseIndex(0);
    }
    sentMessage = true;
}
