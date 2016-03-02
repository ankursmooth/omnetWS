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

    cancelAndDelete(clockwake);
  //  cancelAndDelete(timeoutEvent);
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
        S=R=SF=SL=0;
        WATCH(S);
        WATCH(SF);
        WATCH(SL);
        WATCH(R);
        id=par("nodeId");
        timeout = 1.0;
        delayStats.setName("delay stats");
        delayVector.setName("delay vector");
        RTTStats.setName("RTT stats");
        RTTVector.setName("RTT vector");
        //buf.resize(30);
        //message=NULL;

       // if(wsize<=0){
            wsize=par("k");
        //}
        //if(D_pr<=0){
            D_p=par("D_p");
        //}
            counterofemptyclocks=0;
        clockwake= new cMessage ("clockwake");
        timeoutEvent = new cMessage("timeoutEvent");
        event = new cMessage("event");
        toApp=gate("toApp");
        fromApp=gate("fromApp");
        toPhysical=gate("toPhysical");
        fromPhysical=gate("fromPhysical");
        if(id==1)
        scheduleAt(simTime()+0.1,clockwake);


}

void Dl_layer_GBN::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage())
    {
        if (msg==timeoutEvent){
                    S=0;
                   // scheduleAt(simTime()+timeout,timeoutEvent);
                    cancelEvent(clockwake);
                    cancelEvent(timeoutEvent);
                    scheduleAt(simTime()+0.1,clockwake);
                    S=0;
                    EV<< "\n timeout event, S set to 0"<<S;
                }
        else if (msg==clockwake)
        {
            //EV<<"here";
            scheduleAt(simTime()+0.1,clockwake);
           if((SF+S)<SL ){
               if(buf.size()<=SL && !(SF<(SL-1))){
                   //cancelEvent(clockwake);
                   //do nothing till buffer fills more
                   //check for each clock if buffer filled
                   counterofemptyclocks++;
                   if(counterofemptyclocks>20){
                       cancelEvent(clockwake);
                       bufsize=buf.size();
                       cMessage *msg;
                       for(int i=0;i<bufsize;i++){
                           msg=NULL;
                           msg = dynamic_cast<cMessage *>(buf.at(i));
                           if(msg){
                              delete msg;
                           }
                       }
                   }
               }
               else{
                   counterofemptyclocks=0;
                   if(buf.size()>(SF+S)){
                       EV<<"sending delayed paket "<<(SF +S);
                       cMessage *msgg = buf.at(SF + S)->dup();
                       numSent++;
                   sendDelayed(msgg,D_p,toPhysical);
                   if(S==0){
                       scheduleAt(simTime()+timeout,timeoutEvent);
                   }
                   S++;
                   }

               }

           }

        }

    }
    if(msg->getArrivalGate()==fromApp){

        A_PDU *apkt = check_and_cast<A_PDU *>(msg);
        int seq= apkt->getID();


        sprintf(msgname, "dpdu -%d", (seq));

        DL_PDU *dpkt = new DL_PDU(msgname);
        dpkt->setID((seq)%(wsize+1));
        dpkt->setType("Data");
        dpkt->setSourceAdd(apkt->getSourceAdd());
        dpkt->setDestiAdd(apkt->getDestiAdd());
        dpkt->encapsulate(apkt);

        //cMessage *msg = check_and_cast<cMessage*>(pkt);
        buf.push_back(dpkt);
        // to make sure SL is not more than messages in buffer
        bufsize=buf.size();
        if(SL<bufsize && SL<(SF+wsize)){
            SL++;
        }

    }
    else if(msg->getArrivalGate()==fromPhysical){
        P_PDU *ppkt = check_and_cast<P_PDU *>(msg);
           DL_PDU *pkt =check_and_cast<DL_PDU *>(ppkt->decapsulate());
           sendingTime=pkt->getSendingTime();

            delete ppkt;
            //EV<<"heres";
            numReceived++;
            if(strcmp(pkt->getType(),"Ack")==0){
                delayVector.record((simTime()-sendingTime).dbl());
                delayStats.collect((simTime()-sendingTime).dbl());
                RTTVector.record((simTime()-pkt->getTimestamp()).dbl());
                RTTStats.collect((simTime()-pkt->getTimestamp()).dbl());
                flag=0;
                bufsize=buf.size();
               // EV<<"here"<<bufsize;
               for(S=0;S<SL-SF;S++){
                   if(bufsize>(SF+S+1)){

                   DL_PDU *tmppkt = check_and_cast<DL_PDU *>(buf.at(SF+S+1));
                   if(pkt->getID()==tmppkt->getID()){
                       flag=1;
                   }
                   }
               }
               /*if(S<R){
                   SF= SF + R-S;
               }
               else{
                   SF= SF+ S-R;
               }
                SF=SF+(pkt->getID()+1) - ;
                */
            if(flag){
                   S=(SF%(wsize+1));
                   while(S!=pkt->getID()){
                       SF++;
                       S=(SF%(wsize+1));
                   }
                    S=0;
            }
                    S=0;

                // to make sure SL is not more than messages in buffer
                bufsize=(buf.size());
                SL=(SF+wsize)<bufsize?(SF+wsize):bufsize;
                cancelEvent(timeoutEvent);


                delete pkt;
            }
            else{
                delayVector.record((simTime()-sendingTime).dbl());
                delayStats.collect((simTime()-sendingTime).dbl());
                flag=0;
                if(R== pkt->getID()){
                    sendDelayed(pkt,D_p,toApp);
                    R=R+1;
                    R= R%(wsize+1);

                }
                else
                    flag=1;
                sprintf(msgname, "dpdu ack-%d", ((R) ));
                DL_PDU *dpkt = new DL_PDU(msgname);
                dpkt->setID(R);
                dpkt->setType("Ack");
                dpkt->setSourceAdd(pkt->getDestiAdd());
                dpkt->setDestiAdd(pkt->getSourceAdd());
                numSent++;
                dpkt->setTimestamp(sendingTime);
                sendDelayed(dpkt,D_p,toPhysical);
                if(flag)
                    delete pkt;


            }

            //delete ppkt;


    }



}
void Dl_layer_GBN::finish(){
        EV << "Sent:     " << numSent << endl;
      EV << "Received: " << numReceived << endl;

      recordScalar("#sent", numSent);
      recordScalar("#received", numReceived);

      delayStats.recordAs("delay vectot");
      RTTStats.recordAs("RTT vector");

}
