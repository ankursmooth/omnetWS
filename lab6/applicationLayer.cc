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
    sourceadd=par("sourceadd");
    destiadd=par("destiadd");
//    timeout = 5.0;
//    timeoutEvent = new cMessage("timeoutEvent");
    in=gate("in");
    out=gate("out");
    sentCount=par("noofpackets");
    if(id==sourceadd){
        char msgname[20];
        sprintf(msgname, "APDU data-%d", seq++);
        A_PDU *msg = new A_PDU(msgname);
        msg->setID(seq-1);
        msg->setType("Data");
        msg->setSourceAdd(sourceadd);
        msg->setDestiAdd(destiadd);

        //cMessage *msg2 = check_and_cast<cMessage*>(msg);
        scheduleAt(0,msg);
    }
    if(id==destiadd){
        delayStats.setName("delay stats");
        delayVector.setName("delay vector");
    }

}

void ApplicationLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(msg->isSelfMessage()){
        msg->setTimestamp(simTime());
        send(msg,out);


    }
    else if(sentCount<1){
        delete msg;
    }
    else {
        A_PDU *rpkt = check_and_cast<A_PDU *>(msg);


        if(strcmp(rpkt->getType(),"Data")==0){
            char msgname[20];
            int x=rpkt->getID();
            sprintf(msgname, "APDU ack-%d", x);
            delayVector.record(simTime()-rpkt->getTimestamp());
            delayStats.collect(simTime()-rpkt->getTimestamp());
            A_PDU *pkt = new A_PDU(msgname);
            pkt->setID(x);
            pkt->setType("Ack");
            pkt->setSourceAdd(rpkt->getDestiAdd());
            pkt->setDestiAdd(rpkt->getSourceAdd());
            //cMessage *msg = check_and_cast<cMessage*>(pkt);
            //send(msg,out);
            send(pkt,out);
            delete rpkt;

        }
        else{
            sentCount--;
            char msgname[20];
            sprintf(msgname, "APDU  data-%d", seq++);
            delete rpkt;
            A_PDU *pkt = new A_PDU(msgname);
            pkt->setID(seq-1);
            pkt->setType("Data");
            pkt->setSourceAdd(sourceadd);
            pkt->setDestiAdd(destiadd);
            //cMessage *msg = check_and_cast<cMessage*>(pkt);
            //send(msg,out);
            send(pkt,out);


        }
    }

}
void ApplicationLayer::finish(){
    if(id==destiadd)
        delayStats.recordAs("delay");
}
