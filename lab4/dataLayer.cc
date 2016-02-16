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
    messageWaitcopy= dynamic_cast<cMessage *>(messageWaitcopy);
    message= dynamic_cast<cMessage *>(message);
    /*if(messageWaitcopy)
        delete messageWaitcopy;
    if(message)
    delete message;
    */
}


void DataLayer::initialize()
{
    // TODO - Generated method body
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
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


        send(dpkt,toPhysical);
        cancelEvent(event);
        cancelEvent(timeoutEvent);
        scheduleAt(simTime()+timeout, timeoutEvent);
    }
    if(msg==event){
        msg=messageWaitcopy;
    }
    if(msg->getArrivalGate()==fromApp){

        A_PDU *apkt = check_and_cast<A_PDU *>(msg);
        int seq= apkt->getID();


        sprintf(msgname, "dpdu with apdu-%d", (seq));

        DL_PDU *dpkt = new DL_PDU(msgname);
        dpkt->setID((seq)%2);
        dpkt->setType("Data");
        dpkt->setSourceAdd(apkt->getSourceAdd());
        dpkt->setDestiAdd(apkt->getDestiAdd());
        dpkt->encapsulate(apkt);

        //cMessage *msg = check_and_cast<cMessage*>(pkt);

       message=dpkt;

       EV << "Timer started...\n";
       cancelEvent(timeoutEvent);
       scheduleAt(simTime()+timeout, timeoutEvent);

       cancelEvent(event);
       numSent++;
        send(dpkt,toPhysical);
        if (ev.isGUI())
             updateDisplay();


    }
    else if(msg->getArrivalGate()==fromPhysical){
        P_PDU *ppkt = check_and_cast<P_PDU *>(msg);
           DL_PDU *pkt =check_and_cast<DL_PDU *>(ppkt->decapsulate());

            delete ppkt;
            cancelEvent(event);
            numReceived++;
            if(strcmp(pkt->getType(),"Ack")==0){
                EV << "Timer cancelled. receied ack from data layer\n";
                cancelEvent(timeoutEvent);
                delete pkt;


            }
            else{
                sprintf(msgname, "dpdu ack-%d", (pkt->getID() +1 )%2);
                DL_PDU *dpkt = new DL_PDU(msgname);
                dpkt->setID((pkt->getID() +1 )%2);
                dpkt->setType("Ack");
                dpkt->setSourceAdd(pkt->getDestiAdd());
                dpkt->setDestiAdd(pkt->getSourceAdd());
                numSent++;
                EV<< "sending ack to data layer and forwarding packet to application\n";
                send(dpkt,toPhysical);
                send(pkt,toApp);
            }
            if (ev.isGUI())
                         updateDisplay();
            //delete ppkt;


    }




}
void DataLayer::updateDisplay()
    {
        char buf[40];
        sprintf(buf, "rcvd: %d sent: %d", numReceived, numSent);
        getDisplayString().setTagArg("t",0,buf);
    }

