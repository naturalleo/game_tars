#include "FruitTigerServer.h"
#include "FruitImp.h"

using namespace std;

FruitTigerServer g_app;

/////////////////////////////////////////////////////////////////
void
FruitTigerServer::initialize()
{
    //initialize application here:
    //...

    addServant<FruitImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".FruitObj");
}
/////////////////////////////////////////////////////////////////
void
FruitTigerServer::destroyApp()
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
