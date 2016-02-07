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
//void DataLayer::DataLayer()
//{
//    timeoutEvent = NULL;
//}

DataLayer::~DataLayer(){
    cancelAndDelete(timeoutEvent);
    cancelAndDelete(event);
    delete messageWaitcopy;
    delete message;
}


void DataLayer::initialize()
{
    // TODO - Generated method body
        id=par("nodeId");
        timeout = 5.0;
        //message=NULL;
        timeoutEvent = new cMessage("timeoutEvent");
        event = new cMessage("event");
        toApp=gate("toApp");
        fromApp=gate("fromApp");
        toPhysical=gate("toPhysical");
        fromPhysical=gate("fromPhysical");


}

void DataLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg!=event && msg!=timeoutEvent){
        if(id==1){

            if(msg->getArrivalGate()==fromPhysical){
                if (uniform(0,1) < 0.1)
               {
                   EV << "\"Losing\" message\n";
                   delete msg;
                   return;
               }
            }
            EV << "here...\n";
            if(msg->getArrivalGate()==fromApp){
                messageWaitcopy=msg;
                if( uniform(0,1)<0.3){
                    scheduleAt(simTime()+2.0, event);
                    EV << "waiting at sender for 2 seconds...\n";
                }
                else{
                    scheduleAt(simTime()+1.0, event);
                    EV << "waiting at sender for 1 seconds...\n";
                }
            }
        }
        else if(id==2){
            if(msg->getArrivalGate()==fromPhysical){
                if (uniform(0,1) < 0.15)
               {
                   EV << "\"Losing\" message\n";
                   delete msg;
                   return;
               }
            }
            if(msg->getArrivalGate()==fromApp){
                messageWaitcopy=msg;
                if( uniform(0,1)<0.4){
                    EV << "waiting at receiver for 2 seconds...\n";
                            scheduleAt(simTime()+2.0, event);
                }
                else{
                    EV << "waiting at receiver for 1 seconds...\n";
                    scheduleAt(simTime()+1, event);
                }
            }
        }
    }
    if (msg==timeoutEvent)
    {

        EV << "Timeout expired, resending message and restarting timer\n";

        cMessage *copy = (cMessage *) message->dup();
        DL_PDU *dpkt = check_and_cast<DL_PDU *>(copy);

        P_PDU *pkt = new P_PDU(dpkt->getFullName());


       pkt->setID(dpkt->getID());
       pkt->setType(dpkt->getType());
       pkt->encapsulate(dpkt);
        send(pkt,toPhysical);
        cancelEvent(event);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    if(msg==event){
        msg=messageWaitcopy;
    }
    if(msg->getArrivalGate()==fromApp){

        A_PDU *apkt = check_and_cast<A_PDU *>(msg);
        int seq= apkt->getID();

        char msgname[20];
        sprintf(msgname, "msg-%d", (seq));

        DL_PDU *dpkt = new DL_PDU(msgname);
        dpkt->setID((seq));
        dpkt->setType(apkt->getType());
        dpkt->setSourceAdd(apkt->getSourceAdd());
        dpkt->setDestiAdd(apkt->getDestiAdd());
        dpkt->encapsulate(apkt);

        //cMessage *msg = check_and_cast<cMessage*>(pkt);
        P_PDU *pkt = new P_PDU(msgname);
       pkt->setID((seq));
       pkt->setType(dpkt->getType());
       pkt->encapsulate(dpkt);
       message=dpkt;
       if(strcmp(apkt->getType(),"Data")==0){
           EV << "Timer started...\n";
           scheduleAt(simTime()+timeout, timeoutEvent);
       }
       cancelEvent(event);
        send(pkt,toPhysical);


    }
    else if(msg->getArrivalGate()==fromPhysical){

            P_PDU *ppkt = check_and_cast<P_PDU *>(msg);
            DL_PDU *pkt = new DL_PDU();
            pkt=check_and_cast<DL_PDU *>(ppkt->decapsulate());

            if(strcmp(ppkt->getType(),"Ack")==0){
                EV << "Timer cancelled.\n";
                cancelEvent(timeoutEvent);

            }
            delete ppkt;
            cancelEvent(event);
            send(pkt,toApp);
    }



}
