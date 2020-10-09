#ifndef _H_TYPES_
#define _H_TYPES_

// candides list
typedef enum _Candidates {Joe, Donald} Candid;
// vote structure
typedef struct _Vote {
    Candid candid;
    char *current_hash;
    char *previous_hash;
} Vote;
// chain array
Vote Chain[50];

#endif