#include "GsrTester.hpp"

/**
 * Tests whether the provided GSR value (lightningGsr) is within an acceptable range
 * defined relative to the original GSR value (orgGsr).
 * 
 * @param lightningGsr The GSR value to test.
 * @param orgGsr The reference GSR value to compare against.
 * @return 1 if lightningGsr is within the acceptable range, otherwise 0.
 */
int GsrTester::testGSR(float lightningGsr, float orgGsr) {
    float upper, lower;

    // Handling edge case when original GSR is zero
    if (orgGsr == 0) {
        upper = 0.05;
        lower = -0.05;
    } 
    else if (orgGsr > 0) {
        // Setting bounds for positive original GSR
        upper = orgGsr * 1.5;
        lower = orgGsr * 0.5;
    } 
    else {
        // Setting bounds for negative original GSR
        upper = orgGsr * 0.5;
        lower = orgGsr * 1.5;
    }

    // Checking if the test GSR falls within the bounds
    if (lightningGsr <= upper && lightningGsr >= lower) {
        return 1;  // Accepted
    } else {
        return 0;  // Not accepted
    }
}
