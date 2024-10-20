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

#include "Pier.h"

namespace oblig1 {

Define_Module(Pier);

Pier::Pier() {
    busQueueSize = 0;
    carQueueSize = 0;
    ferryEmptySpots = 70;  // Initialize with the ferry's capacity
}

Pier::~Pier() {
}

void Pier::initialize() {
    queueSizeVector.setName("Pier queue size");
    ferryEmptySpotsVector.setName("Empty spots on ferry");
    queueSizeVector.setInterpolationMode(cOutVector::NONE);
    ferryEmptySpotsVector.setInterpolationMode(cOutVector::NONE);
}

void Pier::handleMessage(cMessage *msg) {
    // Message in simulation console
    EV << "Received " << msg->getName() << endl;

    if (strcmp(msg->getName(), "busEvent") == 0) {
        // Increase the bus queue size
        busQueueSize++;
    } else if (strcmp(msg->getName(), "carEvent") == 0) {
        // Increase the car queue size
        carQueueSize++;
    } else if (strcmp(msg->getName(), "ferryDeparture") == 0) {
        // Reset the ferry's empty spots to the original capacity
        ferryEmptySpots = 70;

        // Try to board buses first
        while (busQueueSize > 0 && ferryEmptySpots > 0) {
            busQueueSize--;
            ferryEmptySpots--;
        }

        // Board cars if there are remaining empty spots
        while (carQueueSize > 0 && ferryEmptySpots > 0) {
            carQueueSize--;
            ferryEmptySpots--;
        }

        // Record the current number of empty spots on the ferry
        ferryEmptySpotsVector.record(ferryEmptySpots);

    } else {
        EV_ERROR << "Unexpected message received: " << msg->getName() << endl;
    }


    // Record the total queue size (buses + cars)
    queueSizeVector.record(busQueueSize + carQueueSize);
}

void Pier::finish() {
}

}
;
