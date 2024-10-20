//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Ferry.h"

namespace oblig1 {

Define_Module(Ferry);

Ferry::Ferry() {
    departureTimer = nullptr;
}

Ferry::~Ferry() {
    if (departureTimer != nullptr) {
        cancelAndDelete(departureTimer);
    }
}

void Ferry::initialize() {
    // Schedule the first departure of the ferry at time 0
    departureTimer = new cMessage("departureTimer");
    scheduleAt(simTime() + 3600, departureTimer); // Schedule the first departure after 60 minutes (3600 seconds)
}

void Ferry::handleMessage(cMessage *msg) {
    if (msg == departureTimer) {
        // The ferry is departing
        cMessage *ferryEvent = new cMessage("ferryDeparture");
        send(ferryEvent, "outFerry");

        // Schedule the next departure in 60 minutes (3600 seconds)
        scheduleAt(simTime() + 3600, departureTimer);

    } else {
        EV_ERROR << "Unexpected message received: " << msg->getName() << endl;
    }
}

}
;
