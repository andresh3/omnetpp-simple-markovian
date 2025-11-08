#pragma once
#include <string.h>
#include <omnetpp.h>


// Class Declaration (would typically be in a seperate .h file)
class Generator : public omnetpp::cSimpleModule
{
private:
    // The newCustomerEvent is a "self event" that is scheduled
    // at initialization with some random wait period.
    // After this wait period, a customer event is dispatched
    // and a new newCustomerEvent is scheduled.
    omnetpp::cMessage *arrivalEvent;
public:
    Generator();
    virtual ~Generator();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(omnetpp::cMessage *msg);
};
