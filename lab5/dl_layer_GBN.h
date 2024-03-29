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

#ifndef __LAB5_DATALAYER_H_
#define __LAB5_DATALAYER_H_

#include <omnetpp.h>
#include "DL_PDU_m.h"
using namespace std;
/**
 * TODO - Generated class
 */
class Dl_layer_GBN : public cSimpleModule
{
private:
   simtime_t timeout;  // timeout

   cMessage *clockwake;
   cMessage *message;
   cMessage *event; // pointer to the event object which we'll use for timing
   cMessage *timeoutEvent;
   int numSent;
   int numReceived;

   cLongHistogram delayStats, RTTStats;
   cOutVector delayVector,RTTVector;

   vector<cMessage *> buf;
   int R,S, SL, SF,wsize;
   int flag;
   int counterofemptyclocks;
  protected:
   char msgname[20];
   simtime_t sendingTime;
   simtime_t tempTime;
   simtime_t D_p;
   int id;
   int bufsize;
    cGate * fromApp, *toApp, * toPhysical, *fromPhysical;

    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
  public:
    Dl_layer_GBN()
    {

    }
    virtual void finish();
    virtual ~Dl_layer_GBN();


};

#endif
