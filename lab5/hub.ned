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

package lab5;

module Hub
{
 	gates:
 	    input in1;
 	    input in2;
 	    output out1;
 	    output out2;
    submodules:
        phLayer1 : PLayer{nodeId=1;}
        phLayer2 : PLayer{nodeId=2;}
    connections :
        phLayer1.toDL --> out1;
        phLayer1.fromDL <-- in1;
        phLayer1.toNode --> phLayer2.fromNode;
        phLayer1.fromNode <-- phLayer2.toNode;
        phLayer2.toDL --> out2;
        phLayer2.fromDL <-- in2;
        
}
