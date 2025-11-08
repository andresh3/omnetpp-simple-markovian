#pragma once
#include <string.h>
#include <omnetpp.h>

class Server : public omnetpp::cSimpleModule
{
private:
    omnetpp::cMessage *currentEvent;
    omnetpp::cMessage *endServiceEvent;
    omnetpp::simsignal_t serviceTime; // service time of an individual event
    omnetpp::simsignal_t totalTime; // total time an event has spent waiting
public:
    Server();
    virtual ~Server();
    bool isIdle();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(omnetpp::cMessage *msg);
};
