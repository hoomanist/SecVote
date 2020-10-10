#ifndef _H_TYPES_
#define _H_TYPES_
// Chain size
#define MAX_CHAIN 50
// candides list
typedef enum _Candidates {Joe, Donald} Candid;
// vote structure
typedef struct _Vote {
    Candid candid;
    char *current_hash;
    char *previous_hash;
} Vote;
struct result {
  int JoeNum;
  int DonaldNum;
};
#endif
