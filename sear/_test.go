package gosear

import "testing"

func TestSEAR(t *testing.T) {
	sear(
		"{
        "operation": "extract",
        "admin_type": "racf-rrsf"
    	}",true
	)
}
