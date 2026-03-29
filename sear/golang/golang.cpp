#include "sear.h"

#include <string>

extern "C" {
    // A function that will be called from Go
    std::string callSEAR(const char *request_json, int length, bool debug) {
        sear_result_t* result = sear(request_as_string, request_length, debug);
    }
}