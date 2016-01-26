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

#include "host.h"


Define_Module(Host);

void Host::initialize()
{
    id=par("hostId");
    seq=0;
    in=gate("in");
    out=gate("out");
    sentCount=0;
    if(id==1){
        char msgname[20];
        sprintf(msgname, "msg-%d", ++seq);
        MyMessage *msg = new MyMessage(msgname);
        msg->setId(seq-1);
        msg->setType("Data");
        msg->setSourceAdd(1);
        msg->setDestinationAdd(2);
        scheduleAt(0,msg);
    }
}

void Host::handleMessage(cMessage *msg)
{
    MyMessage *pkt = check_and_cast<MyMessage *>(msg);
    if(pkt->getSourceAdd()== id){

        send(msg,out);
        sentCount++;

    }
    else if(sentCount>9){
        delete msg;
    }
    else {


        if(strcmp(pkt->getType(),"Data")==0){
            char msgname[20];
            sprintf(msgname, "msg-%d", ++seq);
            delete pkt;
            MyMessage *pkt = new MyMessage(msgname);
            pkt->setId(seq-1);
            pkt->setType("Ack");
            pkt->setSourceAdd(2);
            pkt->setDestinationAdd(1);
            cMessage *msg = check_and_cast<cMessage*>(pkt);
            send(msg,out);

        }
        else{
            char msgname[20];
            sprintf(msgname, "msg-%d", ++seq);
            delete pkt;
            MyMessage *pkt = new MyMessage(msgname);
            pkt->setId(seq-1);
            pkt->setType("Data");
            pkt->setSourceAdd(1);
            pkt->setDestinationAdd(2);
            cMessage *msg = check_and_cast<cMessage*>(pkt);
            send(msg,out);
            sentCount++;
        }
    }

}
