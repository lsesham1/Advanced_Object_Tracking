#include "GsrTester.hpp"

/**
 * The GsrTester class provides a method to test if a given GSR value falls within a specified
 * percentage range of an original GSR value. The range can be adjusted by specifying a multiplier.
 */
class GsrTester {
public:
    /**
     * Tests if the given GSR value (lightningGsr) falls within a dynamic range based on the
     * original GSR value (orgGsr) and an optional range multiplier.
     * 
     * @param lightningGsr The GSR value to test.
     * @param orgGsr The original GSR value.
     * @param multiplier The range multiplier to adjust the tolerance. Default is 1.5 for 50% tolerance.
     * @return 1 if the value is within the range, otherwise 0.
     */
    int testGSR(float lightningGsr, float orgGsr, float multiplier = 1.5);
};

int GsrTester::testGSR(float lightningGsr, float orgGsr, float multiplier) {
    float tolerance = orgGsr * multiplier;

    // Define upper and lower bounds based on the multiplier and original GSR
    float upper = orgGsr + tolerance;
    float lower = orgGsr - tolerance;

    // Simplify the range check when orgGsr is zero
    if (orgGsr == 0) {
        upper = 0.05;  // Upper limit when original GSR is zero
        lower = -0.05; // Lower limit when original GSR is zero
    }

    // Check if lightningGsr is within the bounds
    if (lightningGsr <= upper && lightningGsr >= lower) {
        return 1;  // GSR is within the range
    } else {
        return 0;  // GSR is outside the range
    }
}
