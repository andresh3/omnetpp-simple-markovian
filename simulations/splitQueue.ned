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

// Define our network
network SPLITQUEUE
{
    parameters:
    	@display("bgb=566,229");
    submodules:
        gen: Generator {
            @display("p=46,113");
        }
        queue: Queue {
            parameters:
                @display("p=146,113");
            gates:
                out[1];
        }
        splitter: Splitter {
            @display("p=313,113");
        }
        queue2: Queue {
            parameters:
                @display("p=399,70");
            gates:
                out[1];
        }
        queue3: Queue {
            parameters:
                @display("p=399,155");
            gates:
                out[1];
        }
        server1: Server {
            @display("p=227,113");
        }
        server2: Server {
            @display("p=486,70");
        }
        server3: Server {
            @display("p=486,155");
        }
    connections:
        gen.out --> queue.in;
        queue.out[0] --> server1.in;
        server1.out --> splitter.in;
        splitter.out[0] --> queue2.in;
        splitter.out[1] --> queue3.in;
        queue2.out[0] --> server2.in;
        queue3.out[0] --> server3.in;
}
