#ifndef __UBJ_H_
#define __UBJ_H_

#include "JSMN/jsmn.h"

/**
 * JSON type identifier. Basic types are:
 *   o Object
 *   o Array
 *   o String
 *   o Other primitive: number, boolean (true/false) or null
 */
typedef enum {

    /* Value Types */
    TYPE_NULL    = 'Z',
    TYPE_NOOP    = 'N',
    TYPE_TRUE    = 'T',
    TYPE_FALSE   = 'F',

    TYPE_INT8    = 'i',
    TYPE_INT16   = 'I',
    TYPE_INT32   = 'l',
    TYPE_INT64   = 'L',
    TYPE_FLOAT32 = 'd',
    TYPE_FLOAT64 = 'D',
    TYPE_HPN     = 'H',

    TYPE_STRING  = 'S',

    /* Container Types */
    TYPE_ARRAY   = 'a',
    TYPE_OBJECT  = 'o',

    TYPE_END     = 'E'

} ubj_t;

typedef enum {
    /* Not enough buffer space to write */
    UBJ_ERR_BUFFER = -1,
    /* JSON parse error */
    UBJ_ERR_JSON   = -2,
    /* String is partial JSON, more expected */
    UBJ_WARN_PART  = -3,
    /* Instance not initiated */
    UBJ_ERR_INIT   = -3,
} ubj_retcode;

typedef struct{

} internalState;

typedef struct {
    int binSize, binOffset; // auto reset in fn. 
    int tokenSize, tokenOffset;

    char* charOut;
    jsmntok_t *tokenOut;

    /* Stateful tuff for parsing */
    bool inc_offset = FALSE;

    /* Count of objects */
    int objCount = 0;
    char objects[ DEPTH ];

    ubj_internal internalState; //UBJ->string state
} ubj_instance;

/**
 * Converts JSON string into UBJ (Universal Binary JSON). 
 *
 * inst - UBJ parser instance
 * UBJStr - Universal Binary JSON data in char array
 * @returns bytes written, or negative error code
 */
int ubj_pushJSON( ubj_instance* inst, char* JSONStr );

/**
 * Converts UBJ into JSON strings. 
 * 
 * inst - UBJ parser instance
 * UBJStr - Universal Binary JSON data in char array
 *
 * @returns bytes written, or negative error code
 */
int ubj_pushUBJ( ubj_instance* inst, char* UBJStr );

/**
 * Initializes the Universal Binary JSON parser
 * inc_offset - if true, continue translating into the data address + last position
 *              if false, for the given buffer, write from data_address + 0
 */
void ubjInit( ubj_instance* inst, bool inc_offset );

/**
 * Set the buffers to be written into.
 * 
 * dest - character buffer for JSON String OR binary JSON
 * destSize - size of character buffer destination
 * 
 * tokenDest - destination for intermediate JSMN tokens generated during processing
 *             can be used directly aftewards as well
 * tokenSize - size of destination JSMN token buffer
 */
void ubj_setBuffers( ubj_instance* inst, char* dest, int destSize, jsmntok_t *tokenDest, int tokenSize );

#endif /* __UBJ_H_ */
