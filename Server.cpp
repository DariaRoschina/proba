#include <Ice/Ice.h>
#include <Printer.h>
//#include <Printerclass.h>

using namespace std;
using namespace Demo;
class PrinterI : public Printer {
public:
    virtual string getString(const Ice::Current&);
    virtual  int getSum(const int& a,const int& b, const Ice::Current&);
};
//const string& s, const Ice::Current&
//const int& a,const int& b,
string
PrinterI::
getString(const Ice::Current&)
{
//const string& s, const Ice::Current&
string s="hello";
return s;
    //cout << s << endl;
}
int PrinterI:: getSum(const int& a,const int& b,const Ice::Current&)
{
int sum = a + b;
//cout<<sum<<endl;
return sum;
}
int
main(int argc, char* argv[])
{
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectAdapterPtr adapter =
            ic->createObjectAdapterWithEndpoints("SimplePrinterAdapter", "default -p 10000");
        Ice::ObjectPtr object = new PrinterI;
        adapter->add(object, ic->stringToIdentity("SimplePrinter"));
        adapter->activate();
        ic->waitForShutdown();
    } catch (const Ice::Exception& e) {
        cerr << e << endl;
        status = 1;
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    }
    if (ic) {
        try {
            ic->destroy();
        } catch (const Ice::Exception& e) {
            cerr << e << endl;
            status = 1;
        }
    }
    return status;
}
