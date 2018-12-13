#ifndef _HttpImp_H_
#define _HttpImp_H_

#include "servant/Application.h"
#include "NoHttp.h"

#include "rapidjson/include/rapidjson/document.h"
#include "rapidjson/include/rapidjson/writer.h"
#include "rapidjson/include/rapidjson/stringbuffer.h"

using namespace rapidjson;
using namespace std;
using namespace HappyWms;

/**
 *
 *
 */
class HttpImp : public Servant
{
public:
    /**
     *
     */
    virtual ~HttpImp() {}

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
    bool isParamExist(const multimap<string, string> &mmpParams , const string& sName) const;

    string getValue(const multimap<string, string> &mmpParams , const string& sName) const;

    string toDefault(const string &s, const string &sDefault);

    int doRequest(TarsCurrentPtr current, vector<char> &buffer);

    void parseNormal(multimap<string, string> &mmpParams, const string& sBuffer);

protected:

};






/////////////////////////////////////////////////////
#endif
