#include <stdio.h>
#include <stdlib.h>
int main() {
  char matches[]="01111000000110111100000011";
  int nDirection; 
  int nMatcheSize=sizeof(matches)/sizeof(matches[0])-1;
  int nSharpUpCounter=0; int nSharpDownCounter=0;
  int nHeight=0; int nMaxHeight=0;
  int sharpDown[sizeof(matches)/sizeof(matches[0])]={};
  int sharpUp  [sizeof(matches)/sizeof(matches[0])]={};
  for(int i=0; i<nMatcheSize; i++){ //for each in Array of matches (or mis-matches) do...
    if(matches[i]=='1') { nHeight++; } else{ nHeight--; } //if (is matching) then +1 else -1 to height;
    /*i we view matches as raise in height, we can graph height.
    | 3|      /\              1) We find local max and min of the graph.
    | 2|     /  \             2) For each local max find smallest min so far and record (current max- smallest min) it in "nMaxHeight".
    | 1|/\  /    \    /\      3) While itterating if we find a pair of mins and maxes so that (max-min) is bigger than current "nMaxHeight" update "nMaxHeight" to that (max-min).
    | 0|  \/      \  /  \     I like to imagine this process as tying to throw a ball from each peak to all valleys to the left of that point.
    |-1|           \/    \    after we do it for all peaks highest climb would be throwing of the ball that took longest to reach its valley.
    |-2|__________________\___                    *graph doesn't match input "matches"*
    */
    if(matches[i]>matches[i+1]){ // check for a peak.
      printf("-- @%d=%d\n", i+1, nHeight);
      if(nDirection==0){
        sharpUp[nSharpUpCounter]=nHeight; nSharpUpCounter++;
        
        int nSmallestDown = sharpDown[0];
        for (int j = 0; j < nSharpDownCounter; j++) {//find smallest valley so far.
          if (sharpDown[j] < nSmallestDown) {
            nSmallestDown = sharpDown[j];
          }
        }
        if ((nHeight - nSmallestDown) > nMaxHeight) {//if max-min is bigger than "nMaxHeight" update it.
          nMaxHeight = nHeight - nSmallestDown;
        }
      } nDirection=1;
    }
    else if(matches[i]<matches[i+1]){// check for a valley.
      printf("++ @%d=%d\n", i+1, nHeight);
      if(nDirection==1){
        sharpDown[nSharpDownCounter]=nHeight; nSharpDownCounter++;
      }
      nDirection=0;
    }
  }

  for(int r=0; r<nMatcheSize; r++){
    printf("sharpUp: %d\n",   sharpUp[r]);
  }
  for(int r=0; r<nMatcheSize; r++){
    printf("sharpDown: %d\n", sharpDown[r]);
  }
  printf("%d\n", nMaxHeight);
}
