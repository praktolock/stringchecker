#include "sometree.h"

struct NODE*createnode(char _value)
{
    struct NODE*ret=malloc(sizeof(struct NODE));
    ret->right=NULL;
    ret->bottom=NULL;
    ret->value=_value;
    return(ret);
}

void deletetree(struct NODE*_node)
{
    if(_node->bottom)deletetree(_node->bottom);
    if(_node->right) deletetree(_node->right);
    free(_node);
}

struct NODE*placeright(struct NODE*_what, struct NODE*_where)
{
    _what->right=_where->right;
    _where->right=_what;
    return(_what);
}

struct NODE*hfind(struct NODE*_top, char _value) //horizontal find (-:
{
    struct NODE*cursor=_top;
    while(cursor->value!=_value)
    {
        cursor=cursor->right;
        if(!cursor)return(NULL);
    }
    return(cursor);
}

int checkstring(struct NODE*_top, char*_str)
{
    struct NODE*ncur=_top; //node cursor
    char   *scur    =_str; //string cursor
    while(1)
    {
        ncur=hfind(ncur, *scur);
        if(!ncur)
            return(0);
        if(!*scur && !ncur->value)
            return(1);
        ncur=ncur->bottom;
        scur++;
    }
    return(0);
}

int loadtree(char*filename, struct NODE**_top) //fill tree with strings from file
{
    struct NODE **cursor=_top;
    FILE*fdesc=fopen(filename, "r");
    if(fdesc==NULL)
    {
        printf("fopen error: %s\n", strerror(errno));
        return(0);
    }
    char c;
    while(EOF!=(c=fgetc(fdesc)))
    {
        if(c < 32)c=0;
        if(!*cursor)
        {
            *cursor=createnode(c);
            if(c)
                cursor=&(*cursor)->bottom;
            else
                cursor=_top;
            continue;
        }
        while((*cursor)->value != c)
        {
            //find or create node with value == c, and set cursor to it
            if(!*cursor)
            {
                *cursor=createnode(c);
                break;
            }
            if((*cursor)->value > c)
            {
                struct NODE*tmp=createnode(c);
                tmp->right=*cursor;
                *cursor=tmp;
                continue;
            }
            if((*cursor)->value < c)
            {
                cursor=&(*cursor)->right;
                if(!*cursor)
                {
                    *cursor=createnode(c);
                    break;
                }
                continue;
            }
        }
        if(c)
            cursor=&(*cursor)->bottom;
        else
            cursor=_top;
    }
    fclose(fdesc);
    return(1);
}

void printtree(struct NODE*_node, int lvl)
{
    static char tmpstr[2]={0, 0};
    if(!_node)return;
    int i=0;
    while(lvl!=i++)
        printf(" ");
    tmpstr[0]=_node->value;
    if(!_node->value)tmpstr[0]='0';
    printf("%s\n", tmpstr);
    printtree(_node->bottom, lvl+1);
    printtree(_node->right,    lvl);
}
