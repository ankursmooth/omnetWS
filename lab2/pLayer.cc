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


    toNode=gate("toNode");
    fromNode=gate("fromNode");
    toDL=gate("toDL");
    fromDL=gate("fromDL");
}

void PLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(msg->getArrivalGate()==fromDL){

           DL_PDU *dpkt = check_and_cast<DL_PDU *>(msg);
           int seq= dpkt->getID();
           char msgname[20];
           sprintf(msgname, "msg-%d", (seq)%2);

           P_PDU *pkt = new P_PDU(msgname);
           pkt->setID((seq)%2);
           pkt->setType(dpkt->getType());
           pkt->setSourceAdd(dpkt->getSourceAdd());
           pkt->setDestiAdd(dpkt->getDestiAdd());
           pkt->encapsulate(dpkt);
           //cMessage *msg = check_and_cast<cMessage*>(pkt);
           send(pkt,toNode);


       }
       else if(msg->getArrivalGate()==fromNode){


               send(msg,toDL);
       }
}
