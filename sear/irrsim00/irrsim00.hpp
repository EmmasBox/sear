#ifndef __IRRSIM00_H_
#define __IRRSIM00_H_

#include "sear_result.h"
#include "security_request.hpp"

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