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
network MM1
{
    @display("bgb=566,229");
    submodules:
        gen: Generator {
            @display("p=46,113");
        }
        queue: Queue {
            @display("p=146,113");
        }
        server: Server {
            @display("p=246,113");
        }
    connections:
        gen.out --> queue.in;
        queue.out[0] --> server.in;
}
