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

#ifndef __LAB7_NLAYER_H_
#define __LAB7_NLAYER_H_

#include <omnetpp.h>
#include <bits/stdc++.h>
using namespace std;
/**
 * TODO - Generated class
 */
class NLayer : public cSimpleModule
{
private:
    int nodeId;
    char msgname[20];
    cGate * toport[6], * fromport[6], *toApp, *fromApp;
    map <int, pair<int,int> > m;
    map<int, cGate *> gatemap;
    map<int,char>nameOfNode;
    int seq;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif
