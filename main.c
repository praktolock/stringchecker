#include "sometree.h"
#include <stdio.h>

int main(int argc, char**argv)
{
  char instring[256];
  if(argc<2)
    printf("wrong params\n");
  struct NODE*tree=NULL;
  if(!loadtree(argv[1], &tree))
    return(0);

  //printtree(tree, 0);

  while(1)
  {
    printf(">");
    scanf("%s", instring);
    if(!strcmp(instring, "exit"))
      break;
    if(checkstring(tree, instring))
      printf("YES\n");
    else
      printf("NO\n");
  }

  deletetree(tree);
  return(1);
}
