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

#include "NLayer.h"
#include "A_PDU_m.h"
#include "N_PDU_m.h"
Define_Module(NLayer);

void NLayer::initialize()
{
    // TODO - Generated method body
    nodeId= par("nodeId");
    toApp=gate("toApp");
    fromApp=gate("fromApp");
    for(int i=1;i<6;i++){
        toport[i]=gate("toport",i);
        fromport[i]=gate("fromport",i);
    }

//    toport[2]=gate("toport[2]");
//    toport[3]=gate("toport[3]");
//    toport[4]=gate("toport[4]");
//    toport[5]=gate("toport[5]");
//    fromport[1]=gate("fromport[1]");
//    fromport[2]=gate("fromport[2]");
//    fromport[3]=gate("fromport[3]");
//    fromport[4]=gate("fromport[4]");
//    fromport[5]=gate("fromport[5]");
    if(nodeId==1){
        m[1]=make_pair (0,-1);
        m[2]=make_pair (5,-1);
        m[3]=make_pair (2,-1);
        m[4]=make_pair (3,-1);
        m[5]=make_pair (6,3);
    }
    else if(nodeId==2){
        m[1]=make_pair (5,-1);
       m[2]=make_pair (0,-1);
       m[3]=make_pair (4,-1);
       m[4]=make_pair (8,1);
       m[5]=make_pair (3,-1);
    }
    else if(nodeId==3){
        m[1]=make_pair (2,-1);
       m[2]=make_pair (4,-1);
       m[3]=make_pair (0,-1);
       m[4]=make_pair (5,1);
       m[5]=make_pair (4,-1);
    }
    else if(nodeId==4){
        m[1]=make_pair (3,-1);
       m[2]=make_pair (8,1);
       m[3]=make_pair (5,1);
       m[4]=make_pair (0,-1);
       m[5]=make_pair (9,1);
    }
    else if (nodeId==5){
        m[1]=make_pair (6,3);
       m[2]=make_pair (3,-1);
       m[3]=make_pair (4,-1);
       m[4]=make_pair (9,3);
       m[5]=make_pair (0,-1);
    }
}

void NLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate()==fromApp){
        //
        A_PDU *apkt = check_and_cast<A_PDU *>(msg);

        sprintf(msgname, "npdu with apdu-%d", (apkt->getID()));

        N_PDU *npkt = new N_PDU(msgname);
        npkt->setID(apkt->getID());
        npkt->setType(apkt->getType());
        npkt->setSourceAdd(apkt->getSourceAdd());
        npkt->setDestiAdd(apkt->getDestiAdd());
        npkt->encapsulate(apkt);
        if(m[apkt->getDestiAdd()].second==-1){
            send(npkt,toport[apkt->getDestiAdd()]);
        }
        else if (m[apkt->getDestiAdd()].second>0 && m[apkt->getDestiAdd()].second<6){
            send(npkt,toport[m[apkt->getDestiAdd()].second]);
        }
    }
    else{
        N_PDU *npkt = check_and_cast<N_PDU *>(msg);
        if(npkt->getDestiAdd()==nodeId){
            send(npkt->decapsulate(),toApp);
        }
        else{
            if(m[npkt->getDestiAdd()].second==-1){
                send(npkt,toport[npkt->getDestiAdd()]);
            }
            else if (m[npkt->getDestiAdd()].second>0 && m[npkt->getDestiAdd()].second<6){
                send(npkt,toport[m[npkt->getDestiAdd()].second]);
            }

        }
    }

}
