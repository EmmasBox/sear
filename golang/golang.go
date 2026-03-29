package sear

import "json"
import "fmt"
import "C"

func sear(request struct, debug bool) {

	request_enc, err := json.Marshal(request)

    // Call the SEAR C++ function
    C.callSEAR(request_enc, len(request_enc), debug)
}