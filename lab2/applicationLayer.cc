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

#include "applicationLayer.h"

Define_Module(ApplicationLayer);

void ApplicationLayer::initialize()
{
    // TODO - Generated method body
    id=par("nodeId");
    seq=0;
    in=gate("in");
    out=gate("out");
    sentCount=0;
    if(id==1){
        char msgname[20];
        sprintf(msgname, "msg-%d", ++seq);
        A_PDU *msg = new A_PDU(msgname);
        msg->setID(seq-1);
        msg->setType("Data");
        msg->setSourceAdd(1);
        msg->setDestiAdd(2);
        cMessage *msg2 = check_and_cast<cMessage*>(msg);
        scheduleAt(0,msg2);
    }


}

void ApplicationLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    A_PDU *pkt = check_and_cast<A_PDU *>(msg);
    if(pkt->getSourceAdd()== id){

        send(msg,out);


    }
    else if(sentCount>9){
        delete msg;
    }
    else {


        if(strcmp(pkt->getType(),"Data")==0){
            char msgname[20];
            sprintf(msgname, "msg-%d", ++seq);
            delete pkt;
            A_PDU *pkt = new A_PDU(msgname);
            pkt->setID(seq-1);
            pkt->setType("Ack");
            pkt->setSourceAdd(2);
            pkt->setDestiAdd(1);
            //cMessage *msg = check_and_cast<cMessage*>(pkt);
            //send(msg,out);
            send(pkt,out);

        }
        else{
            char msgname[20];
            sprintf(msgname, "msg-%d", ++seq);
            delete pkt;
            A_PDU *pkt = new A_PDU(msgname);
            pkt->setID(seq-1);
            pkt->setType("Data");
            pkt->setSourceAdd(1);
            pkt->setDestiAdd(2);
            //cMessage *msg = check_and_cast<cMessage*>(pkt);
            //send(msg,out);
            send(pkt,out);

        }
    }

}
