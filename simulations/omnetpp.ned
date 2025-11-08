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

package simplequeue.simulations;


// Define our simple modules, and their parameters
simple Generator
{
    parameters:
        volatile double interarrivalRate; // sec
        @display("i=block/source");
    gates:
        output out;
}
simple Queue
{
    parameters:
        @signal[waitTime](type=simtime_t);
        @statistic[totalWaitTime](source=waitTime; record=vector);
        @display("i=block/queue");
    gates:
        input in;
        output out[];
}

simple Server
{
    parameters:
        volatile double serviceTime;
        @display("i=block/cogwheel");
        @signal[serviceTime](type=simtime_t);
        @signal[totalTime](type=simtime_t);
        @statistic[totalServiceTime](source=serviceTime; record=vector);
        @statistic[totalWaitTime](source=totalTime; record=vector);
    gates:
        input in;
        output out @loose;
}

simple Splitter
{
    parameters:
        volatile double splitProb;
        @display("i=block/fork");
    gates:
        input in;
        output out[2];
}
