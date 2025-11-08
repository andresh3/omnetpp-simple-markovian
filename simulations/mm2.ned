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
network MM2
{
    @display("bgb=566,229");
    submodules:
        gen: Generator {
            @display("p=46,113");
        }
        queue: Queue {
            parameters:
            	@display("p=146,113");
            gates:
                out[2];
        }
        server1: Server {
            @display("p=246,153");
        }
        server2: Server {
            @display("p=246,73");
        }
    connections:
        gen.out --> queue.in;
        queue.out[0] --> server1.in;
        queue.out[1] --> server2.in;
}
