#include<stdio.h>
#include<conio.h>
#include<process.h>
#include <stdlib.h>
#include <string.h>


struct node
{
    char domain[20];
    char pwd[20];
    char expiryDate[12];
    struct node *next;
}*start=NULL,*q,*t;



 
struct node* find(struct node* a,char *x){
  struct node* temp = a;
  while (temp!=0)
  {
    if (strcmp(temp->domain,x)==0)
    {
      return temp;
    }
    temp = temp->next;
  }
  printf("\n\t\t DOMAIN NOT FOUND!!!!");
  return 0;
}

void insert(struct node* t)
{
    t->next=NULL;
    if(start==NULL)     
    {
        start=t;
    }
    else
    {
        q=start;
        while(q->next!=NULL)
        q=q->next;
        q->next=t;
    }
}

void displayP()
{
    if(start==NULL)
    {
        printf("No passworrds are Stored!!!");
    }
    else
    {
        q=start;
        while(q!=NULL)
        {
            printf("\n\tDomain Username : %s",q->domain);printf("    ");printf("Password : %s",q->pwd);
            q=q->next;
        }
        printf("\n");
    }
}
