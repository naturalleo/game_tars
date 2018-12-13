#ifndef _FruitImp_H_
#define _FruitImp_H_

#include "servant/Application.h"
#include "Fruit.h"

/**
 *
 *
 */
class FruitImp : public HappyWms::Fruit
{
public:
    /**
     *
     */
    virtual ~FruitImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     *
     */
    virtual int test(tars::TarsCurrentPtr current) { return 0;};
};
/////////////////////////////////////////////////////
#endif
