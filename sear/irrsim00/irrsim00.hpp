#ifndef __IRRSIM00_H_
#define __IRRSIM00_H_

#ifdef __TOS_390__
#include <unistd.h>
#else
#include "zoslib.h"
#endif

#include <cstddef>
#include <cstdint>

#define CERTIFICATE_MAX_LENGTH 4096
#define APPLICATION_USERID_MAX_LENGTH 248
#define DISTINGUISHED_NAME_MAX_LENGTH 246
#define MAX_REGISTRY_LENGTH 255

/* IRRSIM00 function codes */
const uint16_t RACF_TO_NDS_FUNCTION_CODE     = 0x0003;
const uint16_t NDS_TO_RACF_FUNCTION_CODE     = 0x0004;
const uint16_t RACF_TO_KERB_FUNCTION_CODE    = 0x0005;
const uint16_t KERB_TO_RACF_FUNCTION_CODE    = 0x0006;
const uint16_t DID_TO_RACF_FUNCTION_CODE     = 0x0008;
const uint16_t USER_TO_EMAIL_FUNCTION_CODE   = 0x0009;
const uint16_t EMAIL_TO_USER_FUCTION_CODE    = 0x000A;


#pragma pack(push, 1)  // Don't byte align structure members.

typedef struct {
  char RACF_work_area[1024];
  // return and reason codes
  uint32_t ALET_SAF_rc;
  uint32_t SAF_rc;
  uint32_t ALET_RACF_rc;
  uint32_t RACF_rc;
  uint32_t ALET_RACF_rsn;
  uint32_t RACF_rsn;
  // extract function to perform
  uint8_t function_code;
  uint8_t reserved;
  uint8_t useridLength;
  char userid[8];
  uint32_t certificate_length;
  char certificate[CERTIFICATE_MAX_LENGTH];
  uint16_t application_userid_length;
  char application_userid[APPLICATION_USERID_MAX_LENGTH];
  uint16_t distinguished_name_length;
  char distinguished_name[DISTINGUISHED_NAME_MAX_LENGTH];
  uint16_t registry_name_length;
  char registry_name[MAX_REGISTRY_LENGTH];
} racmap_extract_args_t;

typedef struct {
  char *__ptr32 p_work_area;
  // return and reason code
  uint32_t *__ptr32 p_ALET_SAF_rc;
  uint32_t *__ptr32 p_SAF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rc;
  uint32_t *__ptr32 p_RACF_rc;
  uint32_t *__ptr32 p_ALET_RACF_rsn;
  uint32_t *__ptr32 p_RACF_rsn;
  // extract function to perform
  uint8_t *__ptr32 p_function_code;
  uint8_t *__ptr32 p_userid_length;
  char *__ptr32 p_userid;
  uint32_t *__ptr32 p_certificate_length;
  char *__ptr32 p_certificate;
  uint16_t *__ptr32 p_application_userid_length;
  char *__ptr32 p_application_userid;
  uint16_t *__ptr32 p_distinguished_name_length;
  char *__ptr32 p_distinguished_name;
  uint16_t *__ptr32 p_registry_name_length;
  char *__ptr32 p_registry_name;
} racmap_extract_arg_pointers_t;

// 31-bit for IRRSIM00 arguments.
typedef struct {
  racmap_extract_args_t args;
  racmap_extract_arg_pointers_t arg_pointers;
} racmap_extract_underbar_arg_area_t;


#pragma pack(pop)  // Restore default structure packing options.

// Glue code to call IRRSIM00 assembler code.
extern "C" uint32_t callRmap(char *__ptr32);

#endif