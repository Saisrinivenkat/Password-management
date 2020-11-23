// PROGRAMMING AND DATA STRUCTURES LAB PROJECT
// SAFEKEY SECURE PASSWORD MANAGER

#include<stdio.h>
#include<stdlib.h>
#include<process.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<string.h>
#include "datastructures.c"

int user = -1;
char dirname[] = "database//";
char* getstr(int x)
{
  return malloc(sizeof(char)*x);
}

struct account
{
  char username[30];
  char password[15];
  char mobile[15];
  char gender;
  char emailid[50];
  char dob[11];
  struct node* head;
}
customer;typedef struct account account;

account* getacc()
{
  return malloc(sizeof(account));
}

void login();
void signup();
void logout();
void swap();
void DisplayData();
void Deleteacc();
void storePassword();
void editpassword();
void showPasswords();
void update();
void getpassword();



void  main()
{
  printf("\n #################################### PROGRAMMING AND DATA STRUCTURES LAB PROJECT ####################################\n");
  int choice;
  while (1)
  {

  printf("\n WELCOME TO SAFEKEY SECURE PASSWORD MANAGER \n");
  printf("\n 1.LOGIN ->\n 2.SIGN UP ->\n 3.EXIT ->\n");
  printf("\n >>> Please Select One Of The Options Listed Above To Proceed - ");
  scanf("%d",&choice);
  switch (choice)
  {
  case 1:
    login();
    while(user==1)
    {
      printf("\n *************************************************** WELCOME MR.%s **************************************************\n",customer.username);
      printf("\n 1.Store A New Password ->\n 2.Edit Your Stored Passwords ->\n 3.Swap Your Passwords Between 2 Domains ->\n 4.Show Your Saved Passwords ->\n 5.Display My SafeKey Secure Account Details ->\n 6.LOGOUT From My SafeKey Secure Account ->\n");
      printf("\n >>> Please Select One Of The Options Listed Above To Continue - ");
      scanf("%d",&choice);int el=1;
      switch (choice)
      {
      case 1:
        storePassword();
        break;
      case 2:
        editpassword();
        break;
      case 3:
        swap();
        break;
      case 4:
        do
        {
        printf("\n 1.Display All Your Saved Passwords ->\n 2.Display Your Saved Password For A Particular Domain Username ->\n 3.Go Back To The Previous Menu ->\n ");
        printf("\n >>> Please Select One Of The Options Listed Above To Continue - ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
          displayP();
          break;
        case 2:
          showPasswords();
          break;
        case 3:
          el=0;
          break;
        default:
          printf("\n\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INVALID OPTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ");
          break;
        }
        } while (el==1);
        break;
      case 5:
        do
        {
          printf("\n 1.Display Your SafeKey Secure Account Details ->\n 2.Delete My SafeKey Secure Account Permanently ->\n 3.Update My SafeKey Secure Account Details ->\n 4.Go Back To The Previous Menu ->\n ");
        printf("\n >>> Please Select One Of The Options Listed Above To Continue - ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
          DisplayData();
          break;
        case 2:
          el=0;
          Deleteacc();
          break;
        case 3:
          update();
          break;
        case 4:
          el=0;
          break;
        default:
          printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INVALID OPTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
          break;
        }
        } while (el==1);
        break;
      case 6:
        logout();
        break;
      default:
        printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INVALID OPTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
        break;
      }

    }
    break;
  case 2:
    signup();
    break;
  case 3:
    printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! THANK YOU FOR VISITING US TODAY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    exit(0);
  default:
    printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INVALID OPTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");
    break;
  }
  }
}

int checker(char *arr)
{
  int i =0;
  while (arr[i]!='\0') i++;
  if (i > 6) return 0;
  return 1;
}

char* createPath(char *name)
{
  char filename[20],*filepath = getstr(20);int i=0;
  strcpy(filename,name);
  while (filename[i]!='\0') //Remove Spaces
  {
    if (filename[i]== ' ')
    {
      filename[i] = '_';
    }
    i++;
  }
  strcat(filename,".txt");
  strcpy(filepath,dirname);strcat(filepath,filename);
  return filepath;
}

void loadData(FILE *file)
{
  fscanf(file,"%s\n",customer.username);
  fscanf(file,"%s\n",customer.password);
  fscanf(file,"%s\n",customer.mobile);
  fscanf(file,"%c\n",&customer.gender);
  fscanf(file,"%s\n",customer.emailid);
  fscanf(file,"%s\n",customer.dob);
  char line[100];
  while (!feof(file))
  {
    struct node* passcont = malloc(sizeof(struct node));
    fscanf(file,"%s\n",line);
    strcpy(passcont->domain,line);
    fscanf(file,"%s\n",line);
    strcpy(passcont->pwd,line);
    fscanf(file,"%s\n",line);
    strcpy(passcont->expiryDate,line);
    insert(passcont);
  }
  customer.head = start;
}

int isFound(char *a,char *b){
  FILE *fb = fopen(createPath(a),"r");
  if (fb==NULL)   return 0;
  loadData(fb);
  if (strcmp(customer.password,b)==0)
  {
    fclose(fb);
    return 1;
  }
  fclose(fb);
  return 0;
}

void save()
{
  FILE *fb = fopen(createPath(customer.username),"w+");
  fprintf(fb,"%s\n",customer.username);
  fprintf(fb,"%s\n",customer.password);
  fprintf(fb,"%s\n",customer.mobile);
  fprintf(fb,"%c\n",customer.gender);
  fprintf(fb,"%s\n",customer.emailid);
  fprintf(fb,"%s\n",customer.dob);
  struct node* q = customer.head;
  while (q !=NULL)
  {
    fprintf(fb,"%s\n",q->domain);
    fprintf(fb,"%s\n",q->pwd);
    fprintf(fb,"%s\n",q->expiryDate);
    q = q->next;
  }

  fclose(fb);
}

void savepass(struct node* Aset)
{
  FILE *file = fopen(createPath(customer.username),"a");
  fprintf(file,"%s\n",Aset->domain);
  fprintf(file,"%s\n",Aset->pwd);
  fprintf(file,"%s\n",Aset->expiryDate);
  fclose(file);
}

void swap()
{
  char find1[20],find2[100],temp[20];
  printf("\n >>> Enter The First Domain Username: ");
  scanf("%s",find1);
  printf("\n >>> Enter The Second Domain Username: ");
  scanf("%s",find2);
  struct node* change1 = find(start,find1);
  struct node* change2 = find(start,find2);
  printf("\n >>> Your Password For  The First Domain Username Is : %s\n",change1->pwd);
  printf("\n >>> Your Password For The Second Domain Username Is : %s\n",change2->pwd);
  strcpy(temp,change1->pwd);
  strcpy(change1->pwd,change2->pwd);
  strcpy(change2->pwd,temp);
  save();
  printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR PASSWORDS HAVE BEEN SWAPPED SUCCESSFULLY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

int user_exists(char *name)
{
  FILE *file = fopen(createPath(name),"r");
  if (file!= NULL)
  {
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! THIS USERNAME ALREADY EXISTS !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");fclose(file);
    return 1;
  }
  fclose(file);
  return 0;
}

void signup()
{
  printf("\n ************************************************* SIGN UP ************************************************************\n");
  restart:
  printf("\n >>> Enter Your SafeKey Secure Username : ");
  scanf("%s",customer.username);
  if (user_exists(customer.username))
  {
    goto restart;
  }
  char *p1= getstr(50),*p2 = getstr(50);
  printf("\n >>> Enter Your SafeKey Secure Password : ");scanf("%s",p1);
  printf("\n >>> Confirm Your SafeKey Secure Password : ");scanf("%s",customer.password);
  if (checker(customer.password)){
    printf("\n !!!!!!!!!!!!!!!!!!!!!! YOUR PASSWORD LENGTH SHOULD BE GREATER THAN 6 CHARACTERS, PLEASE TRY AGAIN !!!!!!!!!!!!!!!!!!!!!\n");goto restart;
  }
  if (strcmp(p1,customer.password)!=0 ){
    printf("\n !!!!!!!!!!!!!!!!! THE ENTERED PASSWORDS ARE EITHER DIFFERENT OR VERY SHORT IN LENGTH, PLEASE TRY AGAIN !!!!!!!!!!!!!!!!\n");
    goto restart;
  }
  
  printf("\n >>> Enter Your Mobile Number : (+91) ");
  scanf("%s",customer.mobile);
  printf("\n >>> Enter Your Email Id : ");
  scanf("%s",customer.emailid);
  printf("\n >>> Enter M For Male OR F For Female : ");
  customer.gender = getche();getche();
  printf("\n\n >>> Enter Your Date of Birth (DD/MM/YYYY) : ");
  scanf("%s",customer.dob);
  save();
  printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SIGNED UP SUCESSFULLY !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
  printf("\n KINDLY LOGIN TO CONTINUE \n");
}

void login()
{
  printf("\n *********************************************************** LOGIN *****************************************************\n");
  char *id = getstr(15);
  char *pas = getstr(15);
  printf("\n>>> Enter Your SafeKey Secure Username : ");
  scanf("%s",id);
  printf("\n >>> Enter Your SafeKey Secure Password : ");
  getpassword(pas);printf("\n");
  if (isFound(id,pas))
  {
    user = 1;
    //printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOU HAVE SUCESSFULLY LOGGEG IN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    return;
  }
  printf("\n !!!!!!!!!!!!!!!!!! INCORRECT USERNAME OR PASSWORD, PLEASE TRY AGAIN !!!!!!!!!!!!!!!!!!! \n");

}

void logout()
{
  user = -1;
  printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOU HAVE SUCCESSFULLY LOGGED OUT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
  return;
}

void Deleteacc()
{
  int check = remove(createPath(customer.username));
  if(check==0) printf("\n !!!!!!!!!!!!!!!!!!! YOUR ACCOUNT HAS BEEN PERMANENTLY DELETED !!!!!!!!!!!!!!!!!!!!!!\n");
  user = -1;return;
}

void DisplayData()
{
  printf("\n ***************************************** YOUR SAFEKEY SECURE ACCOUNT DETAILS *****************************************\n ");
  printf("\n >>> Name            : %s",customer.username);
  printf("\n >>> Password        : %s",customer.password);
  printf("\n >>> Mobile Number   : %s",customer.mobile);
  if(toupper(customer.gender)=='M')printf("\n >>> Gender          : Male");
  else if(toupper(customer.gender)=='F')printf("\n >>> Gender          : Female");
  else printf("\n >>> Gender          : Other");
  printf("\n >>> Email ID        : %s",customer.emailid);
  printf("\n >>> Date of Birth   : %s \n",customer.dob);
}


void editpassword()
{
  char finds[20],replace[100];
  printf("\n >>> Enter Your Domain Name : ");
  scanf("%s",finds);
  struct node* change = find(start,finds);
  printf("\n >>> Your Current Password Is : %s.\n",change->pwd);
  printf("\n >>> Enter Your New Password : ");scanf("%s",replace);
  if (checker(replace)){
    printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR PASSWORD LENGTH SHOULD BE GREATER THAN 6 CHARACTERS, PLEASE TRY AGAIN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    return;
  }
  strcpy(change->pwd,replace);
  printf("\n >>> Your Password Has Been Succesfully Changed To : %s.\n",change->pwd);
  save();
} 

void storePassword()
{
  struct node* set = malloc(sizeof(struct node));
  char* id = getstr(20),*pass = getstr(20);
  restart:
  printf("\n >>> Enter Your Domain Username : ");
  scanf("%s",set->domain);
  printf("\n >>> Enter Your Password : ");
  scanf("%s",pass);//getpassword(pass);
  printf("\n >>> Confirm Your Password : ");
  scanf("%s",set->pwd);//getpassword(set->pwd);
  if (checker(set->pwd))
  {
    printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR PASSWORD LENGTH SHOULD BE GREATER THAN 6 CHARACTERS, PLEASE TRY AGAIN !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    return;
  }
  if (strcmp(set->pwd,pass)!=0)
  {
    printf("\n !!!!!!!!!!!!!!!!! THE ENTERED PASSWORDS ARE EITHER DIFFERENT OR VERY SHORT IN LENGTH, PLEASE TRY AGAIN !!!!!!!!!!!!!!!!\n");
    goto restart;
  }
  SYSTEMTIME str;char hold[10];
  GetLocalTime(&str);
  sprintf(hold,"%d",str.wDay);
  strcpy(set->expiryDate,hold);strcat(set->expiryDate,"/");
  sprintf(hold,"%d",str.wMonth);
  strcat(set->expiryDate,hold);
  strcat(set->expiryDate,"/");
  sprintf(hold,"%d",str.wYear);
  strcat(set->expiryDate,hold);
  printf("\n >>> Your Password Has Been Succesfully Saved For The Domain Username %s And Will Expire After %s. \n",set->domain,set->expiryDate);
  insert(set);
  savepass(set);
}

void showPasswords()
{
  char find1[20];
  printf("\n >>> Enter The Domain Username : ");
  scanf("%s",find1);
  struct node* change1 = find(start,find1);
  printf("\n >>> Your Saved Password For The Domain Username %s Is : %s\n ",change1->domain,change1->pwd);
}

void update()
{
  int ch;
  printf("\n<<<< YOUR ACCOUNT INFORMATION >>>>\n\n 1.Mobile Number       : %d\n 2.Date of Birth (DOB) : %s\n 3.Gender              : %c\n 4.Email ID            : %s\n 5.Go Back To The Previous Menu\n\n >>> Please Select One Of The Options Listed Above To Continue - ",customer.mobile,customer.dob,toupper(customer.gender),customer.emailid);
	scanf("%d",&ch);char temp[50];
  switch(ch)
  {
    case 1:
        printf("\n Mobile Number : ");
        scanf("%s",customer.mobile);
        printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR DETAILS HAS BEEN SUCCESSFULLY UPDATED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        break;
    case 2:
        printf("\n Date of Birth (DD/MM/YYYY) :");
        scanf("%s",temp);
        strcpy(customer.dob,temp);
        printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR DETAILS HAS BEEN SUCCESSFULLY UPDATED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        break;
    case 3:
        printf("\n Press M For Male OR F For Female : ");
        customer.gender = getche();getche();
        printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR DETAILS HAS BEEN SUCCESSFULLY UPDATED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        break;
    case 4:
        printf("\n Email ID : ");
        scanf("%s",customer.emailid);
        printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! YOUR DETAILS HAS BEEN SUCCESSFULLY UPDATED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        break;
    case 5:
        break;
    default:
        printf("\n !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! INVALID OPTION !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! \n");break;
  }
  save();
}

void getpassword(char passwd[])
{
    int p=0;
    char character;
    do
    {
        character = getch();
        if(character=='\r')
        break;
        else if(character=='\b')
        {
            printf("\b");//Moves the cursor back
            p--;//Overwrites on the previous letter
        }
        else
        {
        printf("*");
        *(passwd+p)=character;
        p++;
        }
    }
    while(1);
    *(passwd+p) = '\0';

}