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
#include "Vehicle.h"

namespace oblig1 {

Define_Module(Vehicle);

Vehicle::Vehicle() {
    carTimer = nullptr;
    busTimer = nullptr;
}

Vehicle::~Vehicle() {
    // Safe cleanup of scheduled events
    cancelAndDelete(carTimer);
    cancelAndDelete(busTimer);
}

void Vehicle::initialize() {
    carTimer = new cMessage("carTimer");
    busTimer = new cMessage("busTimer");

    scheduleAt(exponential(60), carTimer);
    scheduleAt(exponential(3600), busTimer);
}

void Vehicle::handleMessage(cMessage *msg) {
    if (msg == busTimer) {
        // Bus event logic: buses get priority
        cMessage *busEvent = new cMessage("busEvent");
        send(busEvent, "outBus");

        // Reschedule the busTimer
        scheduleAt(simTime() + exponential(3600), busTimer);

    } else if (msg == carTimer) {
        // Car event logic
        cMessage *carEvent = new cMessage("carEvent");
        send(carEvent, "outCar");

        // Reschedule the carTimer
        scheduleAt(simTime() + exponential(60), carTimer);

    } else {
        EV_ERROR << "Unexpected message received: " << msg->getName() << endl;
    }
}

}
