#include <iostream>
#include <float.h>

// Disables (ON) or enables (OFF) optimizations 
// that could change flag tests and mode changes.
#pragma fenv_access (on) 

using namespace std;

static void tweak_fp_control(unsigned int new_value, unsigned int mask)
{
    unsigned int control_word;
    unsigned int err = _controlfp_s(&control_word, new_value, mask);
    if ( err ) {
        cerr << "error " << err 
             << " when calling _controlfp_s( new_value = " 
             << new_value << ", mask = " << mask << " )" << endl;
    } else
    {
        cout << "successfully called _controlfp_s( new_value = " 
             << new_value << ", mask = " << mask << " )" << endl
             << "new control word = " << control_word << endl;
    }
}


int main( void )
{
    cout << hex;
    cerr << hex;

    double a = 0.1;
    double b=0.1;
    double c;

    // don't set anything but print the current value
    tweak_fp_control(0, 0);  
    // c = 1.0/(a-b);

    // Enable program termination when dividing by zero.
    // This call errors immediately if there already was a divide by zero.
    tweak_fp_control(0, _EM_ZERODIVIDE);  

    try {
        // This gets caught in the debugger.  
        // When running from a dos window it just exits.
        c = 1.0/(a-b);  
    } catch(...) {
        cerr << "error" << std::endl;  // This does not get hit.
    }
    cerr << "hello world\n" << endl;
    return 0;
}
