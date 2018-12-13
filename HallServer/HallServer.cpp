#include "HallServer.h"
#include "HallImp.h"

using namespace std;

HallServer g_app;

/////////////////////////////////////////////////////////////////
void
HallServer::initialize()
{
    //initialize application here:
    //...

    addServant<HallImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".HallObj");
}
/////////////////////////////////////////////////////////////////
void
HallServer::destroyApp()
{
    //destroy application here:
    //...
}
/////////////////////////////////////////////////////////////////
int
main(int argc, char* argv[])
{
    try
    {
        g_app.main(argc, argv);
        g_app.waitForShutdown();
    }
    catch (std::exception& e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }
    return -1;
}
/////////////////////////////////////////////////////////////////
