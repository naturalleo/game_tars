#ifndef _HallImp_H_
#define _HallImp_H_

#include "servant/Application.h"
#include "Hall.h"

/**
 *
 *
 */
class HallImp : public HappyWms::Hall
{
public:
    /**
     *
     */
    virtual ~HallImp() {}

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
