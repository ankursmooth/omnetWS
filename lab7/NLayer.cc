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

#include "NLayer.h"
#include "A_PDU_m.h"
#include "N_PDU_m.h"
#include "R_PDU_m.h"
Define_Module(NLayer);

void NLayer::initialize()
{
    // TODO - Generated method body
    nodeId= par("nodeId");
    toApp=gate("toApp");
    fromApp=gate("fromApp");
    gatemap.clear();
    m.clear();
    nameOfNode[1]='A';
    nameOfNode[2]='B';
    nameOfNode[3]='C';
    nameOfNode[4]='D';
    nameOfNode[5]='E';
    for(int i=0;i<6;i++){
        toport[i]=gate("toport",i);
        fromport[i]=gate("fromport",i);
    }
    seq=0;
    if(nodeId==1){
        m[1]=make_pair (0,-1);
        m[2]=make_pair (5,-1);
        m[3]=make_pair (2,-1);
        m[4]=make_pair (3,-1);
        m[5]=make_pair (10000000,-1);
        gatemap[2]=toport[0];
        gatemap[3]=toport[1];
        gatemap[4]=toport[2];
        scheduleAt(0,new cMessage("start algo"));
    }
    else if(nodeId==2){
        m[1]=make_pair (5,-1);
       m[2]=make_pair (0,-1);
       m[3]=make_pair (4,-1);
       m[4]=make_pair (10000000,-1);
       m[5]=make_pair (3,-1);
       gatemap[1]=toport[0];
       gatemap[3]=toport[1];
       gatemap[5]=toport[2];
    }
    else if(nodeId==3){
        m[1]=make_pair (2,-1);
       m[2]=make_pair (4,-1);
       m[3]=make_pair (0,-1);
       m[4]=make_pair (10000000,-1);
       m[5]=make_pair (4,-1);
       gatemap[1]=toport[0];
       gatemap[2]=toport[1];
       gatemap[5]=toport[2];
    }
    else if(nodeId==4){
        m[1]=make_pair (3,-1);
       m[2]=make_pair (10000000,-1);
       m[3]=make_pair (10000000,-1);
       m[4]=make_pair (0,-1);
       m[5]=make_pair (10000000,-1);
       gatemap[1]=toport[0];

    }
    else if (nodeId==5){
        m[1]=make_pair (10000000,-1);
       m[2]=make_pair (3,-1);
       m[3]=make_pair (4,-1);
       m[4]=make_pair (10000000,-1);
       m[5]=make_pair (0,-1);
       gatemap[2]=toport[0];
       gatemap[3]=toport[1];

    }

}

void NLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
    if(msg->isSelfMessage()){
        map<int,cGate *>::iterator it;
        R_PDU *rpkt= new R_PDU();
        rpkt->setRtable(m);
        rpkt->setSeq(++seq);
        EV<<"sending "<<seq<< "version map" <<" from "<<nameOfNode[nodeId]<<"   ";
        for(it =gatemap.begin(); it!=gatemap.end(); ++it){
            send(rpkt->dup(),it->second);

        }
        delete msg;
    }
    else if(msg->getArrivalGate()==fromApp){
        //
        A_PDU *apkt = check_and_cast<A_PDU *>(msg);

        sprintf(msgname, "npdu with apdu-%d", (apkt->getID()));

        N_PDU *npkt = new N_PDU(msgname);
        npkt->setID(apkt->getID());
        npkt->setType(apkt->getType());
        npkt->setSourceAdd(apkt->getSourceAdd());
        npkt->setDestiAdd(apkt->getDestiAdd());
        npkt->encapsulate(apkt);
        if(m[apkt->getDestiAdd()].second==-1){
            send(npkt,gatemap[apkt->getDestiAdd()]);
        }
        else if (m[apkt->getDestiAdd()].second>0 && m[apkt->getDestiAdd()].second<6){
            send(npkt,gatemap[m[apkt->getDestiAdd()].second]);
        }
    }
    else{
        R_PDU *rpkt=dynamic_cast<R_PDU *>(msg);
        if(rpkt){
            map <int, pair<int,int> > mapreceived;
            mapreceived=rpkt->getRtable();
            int senderId,i;
            bool changed= false;
            for(i=1;i<6;i++){
                // this loop could have been generic using iterators
                if(mapreceived[i].first==0){
                    senderId=i;
                    break;
                }
            }
            if(i==6){
                EV<<"unknown sender";
                delete rpkt;
                return;
            }
            for(i=1;i<6;i++){
                // this loop could have been generic using iterators
                mapreceived[i].first=mapreceived[i].first+ m[senderId].first;
                if(mapreceived[i].first<m[i].first){
                    m[i].first= mapreceived[i].first;
                    m[i].second =senderId;
                    changed=true;
                }
            }
            if(changed){
                scheduleAt(simTime(),new cMessage("start algo"));
            }
            mapreceived.clear();
            delete rpkt;
        }
        else{
            N_PDU *npkt = check_and_cast<N_PDU *>(msg);
            if(npkt->getDestiAdd()==nodeId){
                send(npkt->decapsulate(),toApp);
            }
            else{
                if(m[npkt->getDestiAdd()].second==-1){
                    send(npkt,gatemap[npkt->getDestiAdd()]);
                }
                else if (m[npkt->getDestiAdd()].second>0 && m[npkt->getDestiAdd()].second<6){
                    send(npkt,gatemap[m[npkt->getDestiAdd()].second]);
                }

            }
        }
    }

}
