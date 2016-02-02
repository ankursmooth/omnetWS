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
#include "P_PDU_m.h"
#include "A_PDU_m.h"

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

    if(msg->getArrivalGate()==fromApp){

        A_PDU *apkt = check_and_cast<A_PDU *>(msg);
        int seq= apkt->getID();

        char msgname[20];
        sprintf(msgname, "msg-%d", (seq)%2);

        DL_PDU *pkt = new DL_PDU(msgname);
        pkt->setID((seq)%2);
        pkt->setType(apkt->getType());
        pkt->setSourceAdd(apkt->getSourceAdd());
        pkt->setDestiAdd(apkt->getDestiAdd());
        pkt->encapsulate(apkt);
        //cMessage *msg = check_and_cast<cMessage*>(pkt);
        send(pkt,toPhysical);


    }
    else if(msg->getArrivalGate()==fromPhysical){

            P_PDU *dpkt = check_and_cast<P_PDU *>(msg);
            DL_PDU *pkt = new DL_PDU();
            pkt=check_and_cast<DL_PDU *>(dpkt->decapsulate());
            send(pkt,toApp);
    }

}
