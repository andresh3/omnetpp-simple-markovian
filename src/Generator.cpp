#include "Generator.h"
#include <omnetpp.h>

using namespace omnetpp;
Define_Module(Generator);

Generator::Generator()
{
    arrivalEvent = nullptr;
}

Generator::~Generator()
{
    cancelAndDelete(arrivalEvent);
}


/*
 * When the generator is initialized, we create a new arrival self-event
 * and immediately schedule it's fist occurance according to the arrival rate
 */
void Generator::initialize()
{
    // Recall that the interarrival rate is defined as a function in the
    // parameters (optionally) as a exponential(...)
    arrivalEvent = new cMessage("arrival");
    simtime_t t = simTime() + par("interarrivalRate");
    scheduleAt(t, arrivalEvent);
}

void Generator::finish() {} // Nothing to do here.

/*
 *  The only message the generator expects to receive is a message from itself
 *  to send out an event:
 */
void Generator::handleMessage(cMessage *msg)
{
    // Outgoing event:
    cMessage *arrival = new cMessage("arrival");
    send(arrival,"out");

    simtime_t t = simTime() + par("interarrivalRate");
    scheduleAt(t, arrivalEvent);
}
