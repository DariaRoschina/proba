#include <Ice/Ice.h>
#include <Printer.h>
//#include <Printerclass.h>

using namespace std;
using namespace Demo;

main(int argc, char* argv[])
{
    int a;
    int b;
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
        ic = Ice::initialize(argc, argv);
        Ice::ObjectPrx base = ic->stringToProxy("SimplePrinter:default -p 10000");
        PrinterPrx printer = PrinterPrx::checkedCast(base);
        if (!printer)
            throw "Invalid proxy";

        // printer->printString("!");
        cout << printer->getString() << endl;
        //int a,b;
        //int sum;
       cout << "Введите а и в:" << endl;
       cin>> a;
       cin>> b;
      // printer->getSum(a,b);
        cout<<printer->getSum(a,b)<<endl;

    } catch (const Ice::Exception& ex) {
        cerr << ex << endl;
        status = 1;
    } catch (const char* msg) {
        cerr << msg << endl;
        status = 1;
    }
    if (ic)
        ic->destroy();
    return status;
}
