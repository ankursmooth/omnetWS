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
ApplicationLayer::~ApplicationLayer(){
    cancelAndDelete(timer);
}
void ApplicationLayer::initialize()
{
    // TODO - Generated method body
    id=par("nodeId");
    seq=0;
    numSent = 0;
    numReceived = 0;
    WATCH(numSent);
    WATCH(numReceived);
//    timeout = 5.0;
//    timeoutEvent = new cMessage("timeoutEvent");
    delayStats.setName("delay stats");
    delayVector.setName("delay vector");
    RTTStats.setName("RTT stats");
    RTTVector.setName("RTT vector");
    timer= new cMessage("timer");
    in=gate("in");
    out=gate("out");
    sentCount=51;
    if(id==1){
        //cMessage * msg =new cMessage();
        //cMessage *msg2 = check_and_cast<cMessage*>(msg);
        scheduleAt(0,timer);
    }


}

void ApplicationLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body

    if(sentCount<32){
            delete msg;
    }
    else if(msg->isSelfMessage()){
        char msgname[20];
        //delete msg;
        sprintf(msgname, "APDU data-%d", seq++);
        A_PDU *msg = new A_PDU(msgname);
        msg->setID(seq-1);
        msg->setType("Data");
        msg->setSourceAdd(1);
        msg->setDestiAdd(2);

        msg->setTimestamp();
        send(msg,out);
        cancelEvent(timer);
        scheduleAt(simTime()+0.05,timer);
        numSent++;
        sentCount--;

    }

    else {
        DL_PDU *dpkt = check_and_cast<DL_PDU *>(msg);
        numReceived++;

        A_PDU *pkt = check_and_cast<A_PDU *>(dpkt->decapsulate());
        if(strcmp(pkt->getType(),"Data")==0){
            char msgname[20];
            int x=pkt->getID();
            sprintf(msgname, "APDU ack-%d", x);

            delayapp=simTime()-pkt->getSendingTime();
            delayVector.record(delayapp);
            delayStats.collect(delayapp);
            delete dpkt;
            delete pkt;


        }
        else{

            char msgname[20];
            sprintf(msgname, "APDU  data-%d", seq++);
            delayapp=simTime()-pkt->getSendingTime()+pkt->getTimestamp();
            delete dpkt;
            delete pkt;
            A_PDU *pkt = new A_PDU(msgname);
            pkt->setID(seq-1);
            pkt->setType("Data");
            pkt->setSourceAdd(1);
            pkt->setDestiAdd(2);
            RTTVector.record(delayapp);
            RTTStats.collect(delayapp);
            //cMessage *msg = check_and_cast<cMessage*>(pkt);
            //send(msg,out);
            numSent++;
            pkt->setTimestamp();
            EV<< "sending data from app layer\n";
            send(pkt,out);


        }
    }

}
void ApplicationLayer::finish(){
    delayStats.recordAs("delay");
    RTTStats.recordAs("RTT");
}
