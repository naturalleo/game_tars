#ifndef _HallServer_H_
#define _HallServer_H_

#include <iostream>
#include "servant/Application.h"

using namespace tars;

/**
 *
 **/
class HallServer : public Application
{
public:
    /**
     *
     **/
    virtual ~HallServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();
};

extern HallServer g_app;

////////////////////////////////////////////
#endif
