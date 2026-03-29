package gosear

// #cgo CFLAGS: -std=c99
// #cgo CXXFLAGS: -std=c++17
// #include <sear.h>
import "C"

func sear(request string, debug bool) string {

	C.sear(C.CString(request), C.int(len(request)), C.bool(debug))

	return ""
}
