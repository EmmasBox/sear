#ifndef __IRRSIM00_H_
#define __IRRSIM00_H_

#include "sear_result.h"
#include "security_request.hpp"

#include <cstdint>

/* IRRSIM00 function codes */
const uint16_t RACF_TO_NDS_FUNCTION_CODE     = 0x0003;
const uint16_t NDS_TO_RACF_FUNCTION_CODE     = 0x0004;
const uint16_t RACF_TO_KERB_FUNCTION_CODE    = 0x0005;
const uint16_t KERB_TO_RACF_FUNCTION_CODE    = 0x0006;
const uint16_t DID_TO_RACF_FUNCTION_CODE     = 0x0008;
const uint16_t USER_TO_EMAIL_FUNCTION_CODE   = 0x0009;
const uint16_t EMAIL_TO_USER_FUCTION_CODE    = 0x000A;

/* Prototype for IRRSIM00 */
extern "C" {
void IRRSIM00(char *,               // Workarea
              unsigned int, int *,  // safrc
              unsigned int, int *,  // racfrc
              unsigned int, int *,  // racfrsn
              unsigned int, int *,  // Function code
              int *,                // Option word
              char *,               // RACF userid
              char *,               // Certificate
              char *,               // Application userid
              char *,               // Distinguished name
              char *                // Registry name
);
}

namespace SEAR {
    class IRRSIM00 {
        public:
        void call_irrsim00();
    };
}

#endif