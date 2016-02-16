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

#include "dl_layer_GBN.h"
#include "P_PDU_m.h"
#include "A_PDU_m.h"
using namespace std;
Define_Module(Dl_layer_GBN);
//void DataLayer::DataLayer()
//{
//    timeoutEvent = NULL;
//}

Dl_layer_GBN::~Dl_layer_GBN(){

    cancelAndDelete(timersend);
    messageWaitcopy= dynamic_cast<cMessage *>(messageWaitcopy);
    message= dynamic_cast<cMessage *>(message);
    /*if(messageWaitcopy)
        delete messageWaitcopy;
    if(message)
    delete message;
    */
}


void Dl_layer_GBN::initialize()
{
    // TODO - Generated method body
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);
        id=par("nodeId");
        timeout = 5.0;
        buf.resize(100);
        //message=NULL;
        S=SL=R=SF=0;
        wsize=5;
        event = new cMessage("event");
        toApp=gate("toApp");
        fromApp=gate("fromApp");
        toPhysical=gate("toPhysical");
        fromPhysical=gate("fromPhysical");


}

void Dl_layer_GBN::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if (msg==timersend)
    {

       if(S<SL){
           send(buf.at(S),toPhysical);
           S++;
           scheduleAt(simTime()+0.1,timersend);
       }
    }
    if(msg->getArrivalGate()==fromApp){

        A_PDU *apkt = check_and_cast<A_PDU *>(msg);
        int seq= apkt->getID();


        sprintf(msgname, "dpdu with apdu-%d", (seq));

        DL_PDU *dpkt = new DL_PDU(msgname);
        dpkt->setID((seq));
        dpkt->setType("Data");
        dpkt->setSourceAdd(apkt->getSourceAdd());
        dpkt->setDestiAdd(apkt->getDestiAdd());
        dpkt->encapsulate(apkt);

        //cMessage *msg = check_and_cast<cMessage*>(pkt);
        buf.push_back(dpkt);


    }
    else if(msg->getArrivalGate()==fromPhysical){
        P_PDU *ppkt = check_and_cast<P_PDU *>(msg);
           DL_PDU *pkt =check_and_cast<DL_PDU *>(ppkt->decapsulate());

            delete ppkt;

            numReceived++;
            if(strcmp(pkt->getType(),"Ack")==0){
                S=SF=pkt->getID();
                SL=SF +wsize;
                scheduleAt(simTime()+0.1,timersend);
                delete pkt;
            }
            else{
                sprintf(msgname, "dpdu ack-%d", ((R+1)%wsize ));
                DL_PDU *dpkt = new DL_PDU(msgname);
                dpkt->setID((R+1)%wsize);
                dpkt->setType("Ack");
                dpkt->setSourceAdd(pkt->getDestiAdd());
                dpkt->setDestiAdd(pkt->getSourceAdd());
                numSent++;
                if(R== pkt->getID()){
                    send(pkt,toApp);
                }
                else
                    delete pkt;
                send(dpkt,toPhysical);


            }

            //delete ppkt;


    }



}
