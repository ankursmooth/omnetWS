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

#include "dataLayer.h"

Define_Module(DataLayer);

void DataLayer::initialize()
{
    // TODO - Generated method body
        id=par("nodeId");

        toApp=gate("toApp");
        fromApp=gate("fromApp");
        toPhysical=gate("toPhysical");
        fromPhysical=gate("fromPhysical");


}

void DataLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->getArrivalGate()==fromApp)
        A_PDU *pkt = check_and_cast<A_PDU *>(msg);
    else if(msg->getArrivalGate()==fromPhysical)
        P_PDU *pkt = check_and_cast<P_PDU *>(msg);
    else
        DL_PDU *pkt = check_and_cast<DL_PDU *>(msg);
    if(pkt->getSourceAdd()== id){

        send(msg,toPhysical);
    }
    else {

        int seq= pkt->getID();
        if(strcmp(pkt->getType(),"Data")==0){
            char msgname[20];
            sprintf(msgname, "msg-%d", (++seq)%2);
            delete pkt;
            DL_PDU *pkt = new DL_PDU(msgname);
            pkt->setID((seq-1)%2);
            pkt->setType("Ack");
            pkt->setSourceAdd(2);
            pkt->setDestiAdd(1);
            cMessage *msg = check_and_cast<cMessage*>(pkt);
            send(msg,toApp);

        }
        else{
            char msgname[20];
            sprintf(msgname, "msg-%d", (++seq)%2);
            delete pkt;
            DL_PDU *pkt = new DL_PDU(msgname);
            pkt->setID((seq-1)%2);
            pkt->setType("Data");
            pkt->setSourceAdd(1);
            pkt->setDestiAdd(2);
            cMessage *msg = check_and_cast<cMessage*>(pkt);
            send(msg,toPhysical);

        }
    }
}
