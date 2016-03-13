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

module Node
{
    
    parameters:
        int nodeId;
    gates:
        
        input in[6] @loose ;
        output out[6] @loose;
    submodules:
        aLayer: ApplicationLayer {
            nodeId = nodeId;
            @display("p=310,191");
        }
        dLayer1: DataLayer {
            nodeId = nodeId;
            @display("p=115,191");
        }
        phLayer1: PLayer {
            nodeId = nodeId;
            @display("p=47,191");
        }
        dLayer2: DataLayer {
            nodeId = nodeId;
        }
        phLayer2: PLayer {
            nodeId = nodeId;
        }
        dLayer2: DataLayer {
            nodeId = nodeId;
            @display("p=271,110");
        }
        phLayer2: PLayer {
            nodeId = nodeId;
        }
        dLayer3: DataLayer {
            nodeId = nodeId;
            @display("p=106,50");
        }
        phLayer3: PLayer {
            nodeId = nodeId;
            @display("p=47,50");
        }
        dLayer4: DataLayer {
            nodeId = nodeId;
            @display("p=106,121");
        }
        phLayer4: PLayer {
            nodeId = nodeId;
            @display("p=47,121");
        }
        dLayer5: DataLayer {
            nodeId = nodeId;
            @display("p=218,102");
        }
        phLayer5: PLayer {
            nodeId = nodeId;
            @display("p=179,44");
        }
        nLayer: NLayer {
            nodeId = nodeId;
            @display("p=257,191");
        }

    connections allowunconnected:
        aLayer.out --> nLayer.fromApp;
        nLayer.toApp --> aLayer.in;
        nLayer.toport[1] --> dLayer1.fromApp;
        nLayer.fromport[1] <-- dLayer1.toApp;
        nLayer.toport[2] --> dLayer2.fromApp;
        nLayer.fromport[2] <-- dLayer2.toApp;
        nLayer.toport[3] --> dLayer3.fromApp;
        nLayer.fromport[3] <-- dLayer3.toApp;
        nLayer.toport[4] --> dLayer4.fromApp;
        nLayer.fromport[4] <-- dLayer4.toApp;
        nLayer.toport[5] --> dLayer5.fromApp;
        nLayer.fromport[5] <-- dLayer5.toApp;
        dLayer1.toPhysical --> phLayer1.fromDL;
        phLayer1.toDL --> dLayer1.fromPhysical;
        dLayer2.toPhysical --> phLayer2.fromDL;
        phLayer2.toDL --> dLayer2.fromPhysical;
        dLayer3.toPhysical --> phLayer3.fromDL;
        phLayer3.toDL --> dLayer3.fromPhysical;
        dLayer4.toPhysical --> phLayer4.fromDL;
        phLayer4.toDL --> dLayer4.fromPhysical;
        dLayer5.toPhysical --> phLayer5.fromDL;
        phLayer5.toDL --> dLayer5.fromPhysical;
        phLayer1.fromNode <-- in[1];
        phLayer1.toNode --> out[1];
        phLayer2.fromNode <-- in[2];
        phLayer2.toNode --> out[2];
        phLayer3.fromNode <-- in[3];
        phLayer3.toNode --> out[3];
        phLayer4.fromNode <-- in[4];
        phLayer4.toNode --> out[4];
        phLayer5.fromNode <-- in[5];
        phLayer5.toNode --> out[5];



}
