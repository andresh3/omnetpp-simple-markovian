/*
 * splitter.cpp
 *
 * The splitter should be able to take an input from either a queue, another splitter or from a generator
 *
 * The splitter should only output to a queue or another splitter
 *
 */
#include "Splitter.h"
#include <string.h>
#include <omnetpp.h>
using namespace omnetpp;
Define_Module(Splitter);

Splitter::Splitter() {};
Splitter::~Splitter() {};

void Splitter::initialize() {};
void Splitter::finish() {};
void Splitter::handleMessage(cMessage *msg)
{
    if( uniform(0.0,1.0) < par("splitProb").doubleValue() )
        send(msg, "out", 0);
    else
        send(msg, "out", 1);
}

