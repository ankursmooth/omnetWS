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
    P_PDU *pkt = check_and_cast<P_PDU *>(msg);
        if(msg->isSelfMessage()){

            send(msg,toNode);


        }
        else {

            int seq= pkt->getID();
            if(strcmp(pkt->getType(),"Data")==0){
                char msgname[20];

                sprintf(msgname, "msg-%d", (++seq)%2);
                delete pkt;
                P_PDU *pkt = new P_PDU(msgname);
                pkt->setID((seq-1)%2);
                pkt->setType("Ack");
                pkt->setSourceAdd(2);
                pkt->setDestiAdd(1);
                cMessage *msg = check_and_cast<cMessage*>(pkt);
                send(msg,toDL);

            }
            else{
                char msgname[20];
                sprintf(msgname, "msg-%d", (++seq)%2);
                delete pkt;
                P_PDU *pkt = new P_PDU(msgname);
                pkt->setID((seq-1)%2);
                pkt->setType("Data");
                pkt->setSourceAdd(1);
                pkt->setDestiAdd(2);
                cMessage *msg = check_and_cast<cMessage*>(pkt);
                send(msg,toNode);

            }
        }
}
