// crt_contrlfp_s.c
// processor: x86
// This program uses _controlfp_s to output the FP control 
// word, set the precision to 24 bits, and reset the status to 
// the default.
//
#include <iostream>
#include <float.h>
#pragma fenv_access (on) // Disables (ON) or enables (OFF) optimizations that could change flag tests and mode changes.

using namespace std;
static void tweak_fp_control(unsigned int new_value, unsigned int mask)
{
    // Show original FP control word
    unsigned int control_word;
    unsigned int err = _controlfp_s(&control_word, new_value, mask);
    if ( err ) {
        cerr << "error " << err << " when calling _controlfp_s( new_value = " << new_value << ", mask = " << mask << " )" << endl;
    } else
    {
        cout << "successfully called _controlfp_s( new_value = " << new_value << ", mask = " << mask << " )" << endl
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

    tweak_fp_control(0, 0);
    // c = 1.0/(a-b);
    tweak_fp_control(0, _EM_ZERODIVIDE);

    c = 1.0/(a-b);
    return 0;
}
