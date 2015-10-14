// Goal of this program is to program the USRP settings, setup an RX stream,
// receive N samples, and plot those samples. Might experiment with threading
// and some other things.


#include <iostream>

// UHD Stuff
#include <uhd/utils/safe_main.hpp>
#include <uhd/usrp/multi_usrp.hpp>
#include <uhd/exception.hpp>
#include <uhd/utils/thread_priority.hpp>

// BOOST Stuff
#include <boost/program_options.hpp>
#include <boost/format.hpp>
#include <boost/thread.hpp>

// C Stuff
#include <iostream>
#include <fstream> // Input/Output stream class to operate on files
#include <csignal> // Handle signals
#include <complex> // Class to hold two elements representing complex form


using namespace std;
namespace po = boost::program_options;

// Thread Safe Main Function
int UHD_SAFE_MAIN(int argc, char *argv[]) {
    
    // Try to elevate thread priority for UHD
    uhd::set_thread_priority_safe(1, true);

    // Setup Program Options
    int num_samps;
    double freq, samp_rate, rx_gain, tx_gain, clock_rate;
    std::string args, ref, subdev, antenna;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "Print Help Message")
        ("num_samps", po::value<int>(&num_samps)->default_value(512), "Number of samples to save")
        ("args", po::value<std::string>(&args)->default_value(""), "UHD Device Arguments")
        ("freq", po::value<double>(&freq)->default_value(915e6), "Center Frequency (Hz)")
        ("samp_rate", po::value<double>(&samp_rate)->default_value(2e6), "Sample Rate (Hz)")
        ("rx_gain", po::value<double>(&rx_gain)->default_value(0.0), "RX Gain")
        ("tx_gain", po::value<double>(&tx_gain)->default_value(0.0), "TX Gain")
        ("clock_rate", po::value<double>(&clock_rate), "Set Master Clock")
        ("ref", po::value<std::string>(&ref)->default_value("internal"), "Reference source (internal, external, mimo)")
        ("subdev", po::value<std::string>(&subdev), "Subdevice Specification")
        ("antenna", po::value<std::string>(&antenna), "Antenna Selection")
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

    // Create the USRP
    cout << endl;
    cout << boost::format("Creating USRP Device with: %s...") % args << endl;
    uhd::usrp::multi_usrp::sptr usrp = uhd::usrp::multi_usrp::make(args);
    cout << endl;

    // List Device
    //cout << boost::format("Using Device: %s") % usrp->get_pp_string() << endl;

    // Set USRP Clock Source
    usrp->set_clock_source(ref);

    // Set USRP Master Clock Rate
    if (vm.count("clock_rate")) {
        // If new clock rate specified, try to set (else use default)
        usrp->set_master_clock_rate(clock_rate);
    }
    //cout << boost::format("Master Clock Rate: %f MHz") % ( (usrp->get_master_clock_rate())/1e6 ) << endl << endl;

    // Set the USRP RX Sample Rate
    cout << boost::format("Setting RX Sample Rate: %f MSPS") % (samp_rate/1e6) << endl;
    usrp->set_rx_rate(samp_rate);
    cout << boost::format("Actual RX Sample Rate: %f MSPS") % ( (usrp->get_rx_rate())/1e6 ) << endl << endl;

    // Set the USRP RX Center Frequency
    cout << boost::format("Setting RX Center Frequency: %f MHz") % (freq/1e6) << endl;
    uhd::tune_request_t tune_request(freq);
    usrp->set_rx_freq(tune_request);
    cout << boost::format("Actual RX Center Frequency: %f MHz") % ( (usrp->get_rx_freq())/1e6 ) << endl << endl;

    // Set the USRP RX Gain
    cout << boost::format("Setting RX Gain: %f dB") % (rx_gain) << endl;
    usrp->set_rx_gain(rx_gain);
    cout << boost::format("Actual RX Gain: %f dB") % (usrp->get_rx_gain()) << endl << endl;

    // Set the Antenna
    if (vm.count("antenna")) {
        usrp->set_rx_antenna(antenna);
    }
    cout << boost::format("RX Antenna: %s") % (usrp->get_rx_antenna()) << endl << endl;

    
    

    return EXIT_SUCCESS;
}
