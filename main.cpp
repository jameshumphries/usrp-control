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
    
    //Try to elevate thread priority for UHD
    uhd::set_thread_priority_safe(1, true);

    //Setup Program Options
    int num_samps;
    double freq, samp_rate, rx_gain, tx_gain;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print Help Message")
        ("num_samps", po::value<int>(&num_samps)->default_value(512), "Number of samples to save")
        ("freq", po::value<double>(&freq)->default_value(915e6), "Center Frequency (Hz)")
        ("samp_rate", po::value<double>(&samp_rate)->default_value(2e6), "Sample Rate (Hz)")
        ("rx_gain", po::value<double>(&rx_gain)->default_value(0.0), "RX Gain")
        ("tx_gain", po::value<double>(&tx_gain)->default_value(0.0), "TX Gain")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")){
        cout << desc << endl;
        return EXIT_SUCCESS;
    }

    cout << "Number of Samples: " << num_samps << endl;
    cout << "Center Frequency: " << freq << endl;
    cout << "Sample Rate: " << samp_rate << endl;

    return EXIT_SUCCESS;
}
