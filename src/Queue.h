#pragma once
#include <string.h>
#include <omnetpp.h>


// Class Declaration (would typically be in a seperate .h file)
class Queue : public omnetpp::cSimpleModule
{
private:
    omnetpp::cQueue buffer;
    void sendMessage(); // Private macro for sending next item in queue
    omnetpp::simsignal_t waitTime; // time a msg spends waiting in a queue
public:
    Queue();
    virtual ~Queue();
    bool isEmpty();
    void sendNextArrival();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(omnetpp::cMessage *msg);
};
