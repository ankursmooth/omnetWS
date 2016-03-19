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

#ifndef __LAB7_DATALAYER_H_
#define __LAB7_DATALAYER_H_

#include <omnetpp.h>
#include "DL_PDU_m.h"
/**
 * TODO - Generated class
 */
class DataLayer : public cSimpleModule
{
private:
   simtime_t timeout;  // timeout
   cMessage *timeoutEvent;
   cMessage *message;
   cMessage *event; // pointer to the event object which we'll use for timing
   cMessage *messageWaitcopy;
  protected:
   char msgname[20];
    int id;
    cGate * fromApp, *toApp, * toPhysical, *fromPhysical;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
    DataLayer()
    {
        timeoutEvent = NULL;
    }

    virtual ~DataLayer();


};

#endif
