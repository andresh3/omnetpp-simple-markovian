#pragma once
#include <string.h>
#include <omnetpp.h>

/* splitter.h
 *
 * All the splitter does is split b/w two queues with probability p
 */
class Splitter : public omnetpp::cSimpleModule
{
public:
    Splitter();
    virtual ~Splitter();
protected:
    virtual void initialize();
    virtual void finish();
    virtual void handleMessage(omnetpp::cMessage *msg);
};
