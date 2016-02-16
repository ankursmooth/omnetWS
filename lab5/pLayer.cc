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

#include "pLayer.h"
#include "DL_PDU_m.h"
Define_Module(PLayer);

void PLayer::initialize()
{
    // TODO - Generated method body

    numSent = 0;
    numReceived = 0;
    if(D_p<=0){
        D_p=0.1;
    }
    WATCH(numSent);
    WATCH(numReceived);
    toNode=gate("toNode");
    fromNode=gate("fromNode");
    toDL=gate("toDL");
    fromDL=gate("fromDL");
}

void PLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(msg->getArrivalGate()==fromDL){

//           DL_PDU *dpkt = check_and_cast<DL_PDU *>(msg);
//           int seq= dpkt->getID();
//           char msgname[20];
//           sprintf(msgname, "msg-%d", (seq)%2);
//
//           P_PDU *pkt = new P_PDU(msgname);
//           pkt->setID((seq)%2);
//           pkt->setType(dpkt->getType());
//           pkt->setSourceAdd(dpkt->getSourceAdd());
//           pkt->setDestiAdd(dpkt->getDestiAdd());
//           pkt->encapsulate(dpkt);
           //cMessage *msg = check_and_cast<cMessage*>(pkt);

       DL_PDU *dpkt = dynamic_cast<DL_PDU *> (msg);
        if(dpkt){
            numSent++;

            if(dpkt->getID()==1){
                percentloss=0.1;
            }
            else{
                percentloss=0.15;
            }
            if (uniform(0,1) < percentloss)
           {
               EV << "\"Losing\" message\n";
               delete msg;
               return;
           }
            else{
                sprintf(msgname, "p pdu of dpdu-%d, typ %c", (dpkt->getID()),dpkt->getType()[0]);
                P_PDU *pkt = new P_PDU(msgname);
                pkt->setID((dpkt->getID()));
                pkt->setType(dpkt->getType());
                pkt->encapsulate(dpkt);
                sendDelayed(pkt,D_p,toNode);
            }
        }
        else{
            sendDelayed(msg,D_p,toNode);
        }

       }
       else if(msg->getArrivalGate()==fromNode){

               numReceived++;
               sendDelayed(msg,D_p,toDL);
       }
}
