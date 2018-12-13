#ifndef _FruitTigerServer_H_
#define _FruitTigerServer_H_

#include <iostream>
#include "servant/Application.h"

using namespace tars;

/**
 *
 **/
class FruitTigerServer : public Application
{
public:
    /**
     *
     **/
    virtual ~FruitTigerServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();
};

extern FruitTigerServer g_app;

////////////////////////////////////////////
#endif
