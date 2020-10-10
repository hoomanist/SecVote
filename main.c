#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <readline/readline.h>
#include "types.h"

char *EnumToString(Candid c){
  if(c == Joe)
    return "Joe";
  else
    return "Donald";
}

void appendVote(Vote v, Vote Chain[]){
  int i;
  for(i = 0; i < MAX_CHAIN + 1; i++){
    if(Chain[i].current_hash == NULL){
      break;
    }
  }
  Chain[i] = v;
}

struct result VotesOfCandid(Vote Chain[]){
  struct result output = {0,0};
  for(int i; i < MAX_CHAIN + 1; i++){
    if(Chain[i].current_hash == NULL){
      break;
    }
    else if(Chain[i].candid == Joe){
      output.JoeNum++;
    }
    else if(Chain[i].candid == Donald){
      output.DonaldNum++;
    }
  }
  return output;
}

char *hash (char *buffer, size_t length){
  char *output = (char*) malloc(length + SHA_DIGEST_LENGTH);
  SHA1(buffer, length, output);
  return output;
}

Vote CreateBlock(Vote PreviousBlock, Candid c){
  Vote output;
  output.candid = c;
  char *hashed = hash(EnumToString(c), strlen(EnumToString(c)));
  output.current_hash = hashed;
  output.previous_hash = PreviousBlock.current_hash;
  return output;
}

Vote CreateGenesisBlock(Candid c){
  Vote output;
  output.candid = c;
  output.current_hash = hash(EnumToString(c), strlen(EnumToString(c)));
  return output;
}

char **split(char *line){
  char **output= malloc(2 * sizeof(char*));
  char *token = strtok(line, " ");
  int i = 0;
  while(token != NULL){
    output[i] = token;
    token = strtok(NULL, " ");
    i++;
  }
  return output;
}

Vote LastBlock(Vote Chain[]){
  int i;
  for(i= 0; i < MAX_CHAIN + 1; i++){
    if(Chain[i].current_hash == NULL){
      break;
    }
  }
  return Chain[i-1];
}

int prompt(Vote Chain[]){
  char *input = readline(">>> ");
  char **arguments = split(input);
  if(!(strcmp(arguments[0], "vote"))){
    if(!(strcmp(arguments[1], "joe"))){
      if(Chain[0].current_hash != NULL){
        Vote NewBlock = CreateBlock(LastBlock(Chain), Joe);
        appendVote(NewBlock, Chain);
      }else{
        Vote NewBlock = CreateGenesisBlock(Joe);
        appendVote(NewBlock, Chain);
      }
    }else if(!(strcmp(arguments[1], "donald"))){
      if(Chain[0].current_hash != NULL){
        Vote NewBlock = CreateBlock(LastBlock(Chain), Donald);
        appendVote(NewBlock, Chain);
      }else{
        Vote NewBlock = CreateGenesisBlock(Joe);
        appendVote(NewBlock, Chain);
      }
    }else {
      printf("no such cadid\n");
      return 1;
    }
  }else if(!(strcmp(arguments[0], "stat"))){
    struct result stat = VotesOfCandid(Chain);
    printf("Joe : %d\nDonald : %d\n", stat.JoeNum, stat.DonaldNum);
  } else {
    printf("Syntax error\n");
    return 1;
  }
  return 0;
}

int main() {
 Vote *Chain = malloc(MAX_CHAIN * sizeof(Vote));  
 for(;;){
  prompt(Chain); 
 } 
}
