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

package lab6;

network ForwardingNetwork
{
    submodules:
        n1A: Node {
            nodeId = 1;
            @display("p=89,53");
        }
        n2B: Node {
            nodeId = 2;
            @display("p=252,53");
        }
        n3C: Node {
            nodeId = 3;
            @display("p=157,113");
        }
        n4D: Node {
            nodeId = 4;
            @display("p=72,155");
        }
        n5E: Node {
            nodeId = 5;
            @display("p=252,155");
        }
    connections allowunconnected:
        n1A.in[4] <-- n4D.out[1];
        n4D.in[1] <-- n1A.out[4];
        n1A.in[3] <-- n3C.out[1];
        n3C.in[1] <-- n1A.out[3];
        n1A.in[2] <-- n2B.out[1];
        n2B.in[1] <-- n1A.out[2];
        n2B.in[5] <-- n5E.out[2];
        n5E.in[2] <-- n2B.out[5];
        n2B.in[3] <-- n3C.out[2];
        n3C.in[2] <-- n2B.out[3];
        n5E.in[3] <-- n3C.out[5];
        n3C.in[5] <-- n5E.out[3];

}
