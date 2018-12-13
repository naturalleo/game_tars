/**
 * Tencent is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 */

#include "HttpImp.h"
#include "servant/Application.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include <cctype>
#include <algorithm>


using namespace std;
using namespace tars;

//////////////////////////////////////////////////////
void HttpImp::initialize()
{
    //initialize servant here:
    //...

}

//////////////////////////////////////////////////////
void HttpImp::destroy()
{
    //destroy servant here:
    //...
}



int HttpImp::doRequest(TarsCurrentPtr current, vector<char> &buffer)
{

    try
    {   
        

        TC_HttpRequest request; 
        vector<char> v = current->getRequestBuffer();
        string sBuf;
        sBuf.assign(&v[0],v.size());
        request.decode(sBuf);

        //TLOGDEBUG("getRequestParam : " << request.getRequestParam() << endl);
        TLOGDEBUG("getRequestUrl : " << request.getRequestUrl() << endl);
       // TLOGDEBUG("getRequest : " << request.getRequest() << endl);


        multimap<string, string> _para;
        if (request.isGET() )
        {
            parseNormal(_para, request.getRequestParam());
        }
        else if (request.isPOST() )
        {
            TC_Cgi cgi;
            cgi.parseCgi(request);
            _para = cgi.getParamMap();
        }
        else
            return -1;
        
        if (request.getRequestUrl() == "/phptest/test1" )
        {
        
        } 
        else
        {
            TC_HttpResponse rsp;
            string s = "{\"code\": 2 , \"msg\": \"缺少参数\"}";
            rsp.setResponse(s.c_str(),s.size());
            rsp.encode(buffer);           
        }

    }
    catch(exception &ex)
    {
        current->setResponse(true);
        cout << ex.what() << endl;
    }
    return 0;
}


void HttpImp::parseNormal(multimap<string, string> &mmpParams, const string& sBuffer)
{
    int iFlag = 0;
    string sName;
    string sValue;
    string sTmp;
    string::size_type len = sBuffer.length();
    string::size_type pos = 0;

    while (pos < len)
    {
        sTmp = "";

        if(iFlag == 0)
        {
            while ( (sBuffer[pos] != '=') && (pos < len) )
            {
                sTmp += (sBuffer[pos] == '+') ? ' ' : sBuffer[pos];

                ++pos;
            }
        }
        else
        {
            while ( (sBuffer[pos] != '&') && (pos < len) )
            {
                sTmp += (sBuffer[pos] == '+') ? ' ' : sBuffer[pos];

                ++pos;
            }
        }

        if (iFlag == 0)                         //param name
        {
            sName = TC_Cgi::decodeURL(sTmp);

            if ( (sBuffer[pos] != '=') || (pos == len - 1) )
            {
                sValue = "";

                mmpParams.insert(multimap<string, string>::value_type(TC_Common::trim(sName), sValue));
            }
            else
            {
                iFlag = 1;
            }
        }
        else
        {
            sValue = TC_Cgi::decodeURL(sTmp);

            mmpParams.insert(multimap<string, string>::value_type(TC_Common::trim(sName), sValue));

            iFlag = 0;
        }

        ++pos;
    }
}



bool HttpImp::isParamExist(const multimap<string, string> &mmpParams , const string& sName) const
{
    return mmpParams.find(sName) != mmpParams.end();
}
string HttpImp::toDefault(const string &s, const string &sDefault)
{
    if(s.empty())
    {
        return sDefault;
    }
    return s;
}
string HttpImp::getValue(const multimap<string, string> &mmpParams , const string& sName) const
{
    multimap<string, string>::const_iterator it;

    if((it = mmpParams.find(sName)) != mmpParams.end())
    {
        return it->second;
    }

    return "";
}

