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

Define_Module(DataLayer);

void DataLayer::initialize()
{
    // TODO - Generated method body
        id=par("nodeId");
        seq=0;
        sentCount=0;
        if(id==1){
            char msgname[20];
            sprintf(msgname, "msg-%d", ++seq);
            A_PDU *msg = new A_PDU(msgname);
            msg->setId(seq-1);
            msg->setType("Data");
            msg->setSourceAdd(1);
            msg->setDestiAdd(2);
            scheduleAt(0,msg);
        }
}

void DataLayer::handleMessage(cMessage *msg)
{
    // TODO - Generated method body
}
