//Goal of this program is to program the USRP settings, setup an RX stream,
//receive N samples, and plot those samples. Might experiment with threading
//and some other things.


#include <iostream>

// UHD Stuff
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>
#include <uhd/utils/thread_priority.hpp>

//BOOST Stuff
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>

//C Stuff
#include <iostream>
#include <fstream> // Input/Output stream class to operate on files
#include <csignal> // Handle signals
#include <complex> // Class to hold two elements representing complex form


using namespace std;
namespace po = boost::program_options;

int UHD_SAFE_MAIN(int argc, char *argv[]) {
    
    uhd::set_thread_priority_safe();

    cout << "Hello, TEST!" << endl;
    return 0;
}
