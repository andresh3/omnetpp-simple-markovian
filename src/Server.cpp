#include "Server.h"
#include <omnetpp.h>
#include "Queue.h"
#define BUSY_ICON "block/cogwheel"
#define IDLE_ICON "old/redbox"
using namespace omnetpp;
Define_Module(Server);


Server::Server() {
    currentEvent = nullptr; // Store the current event (customer) being served
    endServiceEvent = nullptr;  // Use a scheduled event to denote when the service is concluded
};
Server::~Server() {
    cancelAndDelete(currentEvent);
    cancelAndDelete(endServiceEvent);
};

void Server::initialize() {
    cDisplayString& display = getDisplayString();
    endServiceEvent = new cMessage("endService");
    display.setTagArg("i", 0, IDLE_ICON);
    serviceTime = registerSignal("serviceTime");
    totalTime = registerSignal("totalTime");
};
void Server::finish() {};

/*
 * The Queue will only receive an incoming arrival and no other events.
 * The behavior should be to automatically put this customer in the queue,
 * check if all available servers are busy, and assign to the first idle
 * server if available. If none are idle, then it is on the server to request
 * an arrival when they are idle.
 */
bool Server::isIdle()
{
    return (currentEvent == nullptr);
}
void Server::handleMessage(cMessage *msg)
{
    cDisplayString& display = getDisplayString();
    cGate *inGate = nullptr;
    cGate *sourceGate = nullptr;
    cGate *outGate = gate("out");
    simtime_t duration;
    // We can either receive an incoming arrival,
    // or we can receive a self-message that our current
    // customer has been finished being helped.
    if(msg == endServiceEvent)
    {
        display.setTagArg("i", 0, IDLE_ICON);
        // Conclude our service
        // If we have an output then forward the event

        // broadcast statistics:
        duration = simTime() - currentEvent->getSendingTime();
        emit(serviceTime,duration);

        duration = simTime() - currentEvent->getCreationTime();
        emit(totalTime, duration);


        if(outGate && outGate->isConnected())
        {
            send(currentEvent,"out");
        }
        // If we don't, then simply delete it
        else
        {
            delete(currentEvent);
        }
        currentEvent = nullptr;


        // request the next available customer in line:
        inGate = gate("in");
        sourceGate = inGate->getPathStartGate();
        cModule *sMod = sourceGate->getOwnerModule();
        Queue *sourceModule = dynamic_cast<Queue*>(sourceGate->getOwnerModule());
        sourceModule->sendNextArrival();
    }
    else
    {
        // set the current event and schedule the service end
        display.setTagArg("i", 0, BUSY_ICON);
        currentEvent = msg;
        simtime_t t = simTime() + par("serviceTime");
        scheduleAt(t, endServiceEvent);
    }
}
