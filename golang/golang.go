package main

// #include <sear.h>
import (
    "fmt"
    "encoding/json"
	"C"
)

func main(request struct, debug bool) {

	request_enc, err := json.Marshal(request)

    // Call the SEAR C++ function
    C.callSEAR(request_enc, len(request_enc), debug)
}