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

package oblig1.simulations;

import oblig1.Vehicle;
import oblig1.Pier;
import oblig1.Ferry;


network FerrySimulation
{
    @display("bgb=646.674,443.226");

    submodules:
        pier: Pier {
            @display("p=285.45,196.182");
        }
        vehicle: Vehicle {
            @display("p=108.99,118.332");
        }
        ferry: Ferry {
            @display("p=108.99,274.032");
        }
    connections:
        vehicle.outBus --> pier.impBus;
        vehicle.outCar --> pier.impCar;
        ferry.outFerry --> pier.impFerry;
}