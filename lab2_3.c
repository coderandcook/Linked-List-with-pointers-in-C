#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch();
void ungetch(int c);
int getword(char *word, int lim);
static struct node2d *p = NULL;//pointer kept at the beginning of the word_list
static struct node2d *p2 = NULL;//at the end
struct node2d;
struct node1d;

struct node1d{
  struct node1d *next; //pointer to the next node
  char *name;//name of node
};
struct node2d{
  struct node1d *first;
  char *name;
  struct node2d *down;//points to the next newest node
};

int main(int argc, char *argv[argc]){
  char word[100];
  int i=0;

  while(getword(word, 100)!=EOF){
    if(strcmp(word, "insert2d")==0){
      char *name1 = (char *)malloc(sizeof(char)*20);
      getword(name1, 20);

      struct node2d* n = NULL;
      n = (struct node2d*) malloc(sizeof(struct node2d));
      n->name = (char *)malloc(sizeof(char)*20);
      n->down = p;
      n->first = NULL;
      n->name = name1;
      //free(name1);
      p = (struct node2d*) malloc(sizeof(struct node2d));

      p->down = n;
      p2 = (struct node2d*) malloc(sizeof(struct node2d));
      p2->down = n;


    }
    else if(strcmp(word, "append2d")==0){
      char *name1 = (char *)malloc(sizeof(char)*20);
      getword(name1, 20);
      struct node2d* n = NULL;
      n = (struct node2d*) malloc(sizeof(struct node2d));
      n->name = (char *)malloc(sizeof(char)*20);

      p2->down->down = n;
      n->down = NULL;
      n->first = NULL;
      n->name = name1;
      //free(name1);
      p2 = (struct node2d*) malloc(sizeof(struct node2d));
      p2->down = n;

    }
    else if(strcmp(word, "appendAfter2d")==0){
      char *name1 = (char *)malloc(sizeof(char)*20);
      getword(name1, 20);
      char *name2 = (char *)malloc(sizeof(char)*20);
      getword(name2, 20);

      struct node2d* n = NULL;
      n = (struct node2d*) malloc(sizeof(struct node2d));
      n->name = (char *)malloc(sizeof(char)*20);

      n->first = NULL;

      struct node2d* temp = p;
      temp = temp->down;
      while(temp!=NULL){
        if (strcmp(temp->name, name2)==0){
          free(name2);
          n->down = temp->down;
          temp->down = n;
          n->name = name1;
          break;
        }

        temp = temp->down;
      }
      if(temp==NULL){
        printf("error: no such 2D node exists.\n");
        return 0;
      }
    }
    else if(strcmp(word, "insert1d")==0){
      char *name1 = (char *)malloc(sizeof(char)*20);
      getword(name1, 20);
      char *name2 = (char *)malloc(sizeof(char)*20);
      getword(name2, 20);

      struct node1d* n1 = NULL;
      n1 = (struct node1d*)malloc(sizeof(struct node1d));
      n1->name = (char *)malloc(sizeof(char)*20);
      n1->next = NULL;

      //find node2d
      struct node2d* temp = p;
      temp = temp->down;
      while(temp!=NULL){
        if(strcmp(temp->name,name2)==0){
          if(temp->first == NULL){
            temp->first = n1;
            n1->name = name1;
          }
          else{
            n1->next = temp->first;
            temp->first = n1;
            n1->name = name1;
          }
          break;
        }
        temp = temp->down;
      }
      if(temp==NULL){
        printf("error: no such 2D node exists.\n");
        return 0;
      }


      //free(name1);
      //free(name2);

    }
    else if(strcmp(word, "printAll")==0){
      struct node2d* temp = p;
      temp = temp->down;
      while(temp!=NULL){
        printf("2d node name=%s\n", temp->name);
        if(temp->first!=NULL){
          struct node1d* temp1 = temp->first;

          while(temp1!=NULL){
            printf("  1d node name=%s\n", temp1->name);
            temp1 = temp1->next;
          }
        }
        temp=temp->down;
      }
    }
    else if(strcmp(word, "print1dList")==0){
      char *name1 = (char *)malloc(sizeof(char)*20);
      getword(name1, 20);

      struct node2d* temp = p;
      temp = temp->down;
      while(temp!=NULL){
        if(strcmp(temp->name, name1)==0){
          printf("2d node name=%s\n", temp->name);
          struct node1d* temp1 = temp->first;
          while(temp1!=NULL){
            printf("  1d node name=%s\n", temp1->name);
            temp1 = temp1->next;
          }
          break;
        }
        temp=temp->down;
      }
      if(temp==NULL){
        printf("error: no such 2D node exists.\n");
        return 0;
      }
    }
    else{
      printf("error: exit loop.\n");
      return 0;
    }
  }


}


int getch(){
  return (bufp>0) ? buf[--bufp] : getchar();
}
void ungetch(int c){
  if(bufp >= BUFSIZE) printf("ungetch: too many chars\n");
  else buf[bufp++] = c;
}
int getword(char *word, int lim){
  int c;
  int getch(void);
  void ungetch(int);
  char *w = word;

  while(isspace(c=getch()));
  if(c!=EOF) *w++ = c;
  if(!isalpha(c)){
    *w = '\0';
    return c;
  }
  for( ; --lim>0; w++)
    if(!isalnum(*w = getch())){
      ungetch(*w);
      break;
    }

  *w = '\0';
  return word[0];
}
