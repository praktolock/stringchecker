#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//  cat
//  car
//  card
//  cow
//  vc
//
//   (root)
//      0-->c------->v
//          |        |
//          a----->o c
//          |      | |
//          r--->t w 0
//          |    | |
//          0->d 0 0
//             |
//             0

struct NODE
{
  struct NODE*right,*bottom;
  char value;
};

struct NODE*createnode(char _value);
void deletetree(struct NODE*_node);

struct NODE*placeright(struct NODE*_what, struct NODE*_where);
struct NODE*hfind(struct NODE*_top, char _value);
int  loadtree(char*filename, struct NODE**_top);
int  checkstring(struct NODE*_top, char*_str);
void printtree(struct NODE*_node, int lvl);
