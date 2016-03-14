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

package lab6way2;

module Node
{
    
    parameters:
        int nodeId;
        int k;
    gates:
        
        input in[k] @loose ;
        output out[k] @loose;
    submodules:
        aLayer: ApplicationLayer {
            nodeId = nodeId;
            @display("p=310,191");
        }
        dLayer[k]: DataLayer {
            nodeId = nodeId;
            @display("p=115,191");
        }
        phLayer[k]: PLayer {
            nodeId = nodeId;
            @display("p=47,191");
        }
        
        nLayer: NLayer {
            nodeId = nodeId;
            kk=k;
            @display("p=257,191");
        }

    connections allowunconnected:
        aLayer.out --> nLayer.fromApp;
        nLayer.toApp --> aLayer.in;
        // for loop in connections
     for i=0..(k-1)
        {
        nLayer.fromport[i] <-- dLayer[i].toApp;
        nLayer.toport[i] --> dLayer[i].fromApp;   
        phLayer[i].toDL --> dLayer[i].fromPhysical;
        dLayer[i].toPhysical --> phLayer[i].fromDL;
        phLayer[i].fromNode <-- in[i];
        phLayer[i].toNode --> out[i];     
        }
//        nLayer.toport[] --> dLayer2.fromApp;
//        nLayer.fromport[2] <-- dLayer2.toApp;
//        nLayer.toport[3] --> dLayer3.fromApp;
//        nLayer.fromport[3] <-- dLayer3.toApp;
//        nLayer.toport[4] --> dLayer4.fromApp;
//        nLayer.fromport[4] <-- dLayer4.toApp;
//        nLayer.toport[5] --> dLayer5.fromApp;
//        nLayer.fromport[5] <-- dLayer5.toApp;
//        dLayer1.toPhysical --> phLayer1.fromDL;
//        phLayer1.toDL --> dLayer1.fromPhysical;
//        dLayer2.toPhysical --> phLayer2.fromDL;
//        phLayer2.toDL --> dLayer2.fromPhysical;
//        dLayer3.toPhysical --> phLayer3.fromDL;
//        phLayer3.toDL --> dLayer3.fromPhysical;
//        dLayer4.toPhysical --> phLayer4.fromDL;
//        phLayer4.toDL --> dLayer4.fromPhysical;
//        dLayer5.toPhysical --> phLayer5.fromDL;
//        phLayer5.toDL --> dLayer5.fromPhysical;
//        phLayer1.fromNode <-- in[1];
//        phLayer1.toNode --> out[1];
//        phLayer2.fromNode <-- in[2];
//        phLayer2.toNode --> out[2];
//        phLayer3.fromNode <-- in[3];
//        phLayer3.toNode --> out[3];
//        phLayer4.fromNode <-- in[4];
//        phLayer4.toNode --> out[4];
//        phLayer5.fromNode <-- in[5];
//        phLayer5.toNode --> out[5];
//


}
