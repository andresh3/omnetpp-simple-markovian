#include "Queue.h"
#include "Server.h"
#include "Splitter.h"
#include <omnetpp.h>
#include <vector>
#include <string.h>
using namespace omnetpp;

Define_Module(Queue);


// Nothing to do here (no pointers :) )
Queue::Queue() {};
Queue::~Queue() {};

// Private macro for sending next arrival; we don't want to
// repeat code to look thru available servers
void Queue::sendMessage()
{
    // Look through all connected out gates:
    cGate* currentOutputGate;
    cGate* endGate;
    Server *destModule;
    simtime_t duration;
    bool splitter = false;

    std::vector<std::string> gates = getGateNames();

    // Break execution if the buffer is empty:
    if(buffer.isEmpty())
        return;

    // Iterate through out out gate vector,
    // and send our arrival to the first non-busy server
    int numGates = gateSize("out");
    for(int i=0;i<numGates;i++)
    {
        currentOutputGate = gate("out",i);
        endGate = currentOutputGate->getPathEndGate();
        destModule = dynamic_cast<Server*>(endGate->getOwnerModule());

        // If the destModule is not a server it must be a splitter so let's cast to that instead:
        if(destModule == nullptr)
            splitter = true;

        if(splitter || destModule->isIdle())
        {
            cMessage *m = (cMessage*)buffer.pop(); // fetch our message
            // Send statistics out:
            duration = simTime() - m->getArrivalTime();
            emit(waitTime, duration);

            // Send it out!
            send(m, "out", i);
            return; // Break execution.
        }
    }


}

// TODO: Add data collection in the following functions:
void Queue::initialize() {
    waitTime = registerSignal("waitTime");
};
void Queue::finish() {};

/*
 * The Queue will only receive an incoming arrival and no other events.
 * The behavior should be to automatically put this customer in the queue,
 * check if all available servers are busy, and assign to the first idle
 * server if available. If none are idle, then it is on the server to request
 * an arrival when they are idle.
 */
void Queue::sendNextArrival()
{
    // See docs for this method: https://doc.omnetpp.org/omnetpp/api/group__Misc.html#ga8e54030c665b5254da268db865fccdfc
    Enter_Method("sendNextArrival()");
    sendMessage();

}
void Queue::handleMessage(cMessage *msg)
{
    buffer.insert(msg);
    sendMessage();

}
