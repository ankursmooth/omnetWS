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
#include "DL_PDU_m.h"

Define_Module(ApplicationLayer);

//void ApplicationLayer::ApplicationLayer()
//{
//    timeoutEvent = NULL;
//}
//
//void ApplicationLayer::~ApplicationLayer(){
//    cancelAndDelete(timeoutEvent);
//}

void ApplicationLayer::initialize()
{
    // TODO - Generated method body
    id=par("nodeId");
    seq=0;
//    timeout = 5.0;
//    timeoutEvent = new cMessage("timeoutEvent");
    in=gate("in");
    out=gate("out");
    sentCount=51;
    if(id==1){
        char msgname[20];
        sprintf(msgname, "msg-%d", ++seq);
        A_PDU *msg = new A_PDU(msgname);
        msg->setID(seq-1);
        msg->setType("Data");
        msg->setSourceAdd(1);
        msg->setDestiAdd(2);

        //cMessage *msg2 = check_and_cast<cMessage*>(msg);
        scheduleAt(0,msg);
    }


}

void ApplicationLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(msg->isSelfMessage()){
        send(msg,out);


    }
    else if(sentCount<2){
        delete msg;
    }
    else {
        DL_PDU *dpkt = check_and_cast<DL_PDU *>(msg);

        A_PDU *pkt = new A_PDU();
        pkt = check_and_cast<A_PDU *>(dpkt->decapsulate());
        if(strcmp(pkt->getType(),"Data")==0){
            char msgname[20];
            int x=pkt->getID();
            sprintf(msgname, "msg-%d", x);
            delete pkt;
            A_PDU *pkt = new A_PDU(msgname);
            pkt->setID(x);
            pkt->setType("Ack");
            pkt->setSourceAdd(2);
            pkt->setDestiAdd(1);
            //cMessage *msg = check_and_cast<cMessage*>(pkt);
            //send(msg,out);
            send(pkt,out);

        }
        else{
            sentCount--;
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
