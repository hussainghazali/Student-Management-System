/*Design Student Management System using structure.
The system should be able to display the IDs and Names of the students stored in it. 
T0he System should be able to delete any student's record with the help of Student ID.
Keep in mind that IDs of any two students can't be same or it will cause ambiguity while deleting the record */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

#define Student struct Stud

struct Stud
{
    char name[100];
    int roll;
    float sgpa[8];
    float cgpa;
};

void printChar(char ch,int n)
{
    while(n--)
    {
        putchar(ch);
    }
}

void printHead()
{ system("cls");

printf("\n\n\t");
printChar('=',16);
printf("[STUDENT] [MANAGEMENT] [SYSTEM]");
printChar('=',16);
printf("\n");
}

void ADD_RECORD(FILE * MY_FILE_SECTION_A)
{
printHead();

char another='y';
Student s;
int i;
float cgpa;

fseek(MY_FILE_SECTION_A,0,SEEK_END);
while(another=='y'||another=='Y')
{

    printf("\n\n\t\tEnter Full Name of Student :--> ");
    fflush(stdin);
    fgets(s.name,100,stdin); 
    s.name[strlen(s.name)-1]='\0';
    printf("\n\n\t\tEnter Roll number :--> ");
    scanf("%d",&s.roll);

    printf("\n\n\tEnter SGPA for 8 semesters :--> \n");
    for(i=0,cgpa=0;i<8;i++)
    {scanf("%f",&s.sgpa[i]);
    cgpa+=s.sgpa[i];

    }

    cgpa/=8.0;
    s.cgpa=cgpa;

    fwrite(&s,sizeof(s),1,MY_FILE_SECTION_A);

    printf("\n\n\t\tWant to enter another student info (Y/N) :--> ");
    fflush(stdin);
    another=getch();
}
}

FILE * DELETE_RECORD(FILE * MY_FILE_SECTION_A)
{
 printHead();

Student s;
int flag=0,tempRoll,siz=sizeof(s);
FILE *TEMP_MY_FILE_SECTION_A;

if((TEMP_MY_FILE_SECTION_A=fopen("temp_student_management_system.txt","wb+"))==NULL)
{
    printf("\n\n\t\t\t\\t :--> ERROR <--: \n\t\t");
    system("pause");
     return MY_FILE_SECTION_A;
}

printf("\n\n\tEnter Roll number of Student to Delete the Record :--> ");
printf("\n\n\t\t\tRoll No. :--> ");
scanf("%d",&tempRoll);

rewind(MY_FILE_SECTION_A);


while((fread(&s,siz,1,MY_FILE_SECTION_A))==1)
{
    if(s.roll==tempRoll)
    { flag=1;
    printf("\n\tRecord Deleted for :--> ");
    printf("\n\n\t\t%s\n\n\t\t%s\n\n\t\t%d\n\t",s.name,s.roll);
    continue;
    }

    fwrite(&s,siz,1,TEMP_MY_FILE_SECTION_A);
}


fclose(MY_FILE_SECTION_A);
fclose(TEMP_MY_FILE_SECTION_A);

remove("student_management_system.txt");
rename("temp_student_management_system.txt","student_management_system.txt");

if((MY_FILE_SECTION_A=fopen("student_management_system","rb+"))==NULL)
{
    printf(":--> ERROR <--:");
    return  NULL;
}

if(flag==0) printf("\n\n\t\t :--> ERROR RECORD NOT FOUND <--: \n\t");

printChar('-',65);
printf("\n\t");
system("pause");
return MY_FILE_SECTION_A;
}

void MODIFY_RECORD(FILE * MY_FILE_SECTION_A)
{
printHead();

Student s;
int i,flag=0,tempRoll,siz=sizeof(s);
float cgpa;

printf("\n\n\tEnter Roll Number of Student to MODIFY the Record :--> ");
scanf("%d",&tempRoll);

rewind(MY_FILE_SECTION_A);

while((fread(&s,siz,1,MY_FILE_SECTION_A))==1)
{
    if(s.roll==tempRoll)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
    fseek(MY_FILE_SECTION_A,-siz,SEEK_CUR);
    printf("\n\n\t\t :--> RECORD FOUND");
    printf("\n\n\t\tEnter New Data for the Record :--> ");

    printf("\n\n\t\tEnter Full Name of Student :--> ");
    fflush(stdin);
    fgets(s.name,100,stdin);
    s.name[strlen(s.name)-1]='\0';

    printf("\n\n\t\tEnter Roll number :--> ");
    scanf("%d",&s.roll);


    printf("\n\n\tEnter SGPA for 8 semesters :--> \n");
    for(i=0,cgpa=0;i<8;i++)
    {scanf("%f",&s.sgpa[i]);
    cgpa+=s.sgpa[i];

    }
    cgpa=cgpa/8.0;


    fwrite(&s,sizeof(s),1,MY_FILE_SECTION_A);
}

else printf("\n\n\t!!!! ERROR :--> RECORD NOT FOUND");

printf("\n\n\t");
system("pause");

}

void DISPLAY_RECORD(FILE * MY_FILE_SECTION_A)
{   printHead();
    Student s;
    int i,siz=sizeof(s);

    rewind(MY_FILE_SECTION_A);

    while((fread(&s,siz,1,MY_FILE_SECTION_A))==1)
    {
        printf("\n\t\tNAME :--> %s",s.name);
        printf("\n\n\t\tROLL :--> %d",s.roll);
        printf("\n\n\tSGPA :--> ");

        for(i=0;i<8;i++)
            printf("| :--> %.2f |",s.sgpa[i]);
        printf("\n\n\t\tCGPA :--> %.2f\n\t",s.cgpa);
        printChar('-',65);
    }
    printf("\n\n\n\t");
     printChar('*',65);
    printf("\n\n\t");
    system("pause");
}

void SEARCH_RECORD(FILE *MY_FILE_SECTION_A)
{printHead();

int tempRoll,flag,siz,i;
Student s;
char another='y';

siz=sizeof(s);

while(another=='y'||another=='Y')
{
printf("\n\n\tEnter Roll Number of Student to search the record :--> ");
scanf("%d",&tempRoll);

rewind(MY_FILE_SECTION_A);

while((fread(&s,siz,1,MY_FILE_SECTION_A))==1)
{
    if(s.roll==tempRoll)
        {flag=1;
        break;
        }
}

if(flag==1)
    {
    printf("\n\t\tNAME :--> %s",s.name);
        printf("\n\n\t\tROLL :--> %d",s.roll);
        printf("\n\n\tSGPA :--> ");

        for(i=0;i<8;i++)
            printf("| :--> %.2f |",s.sgpa[i]);
        printf("\n\n\t\tCGPA :--> %.2f\n\t",s.cgpa);
        printChar('-',65);

}
else printf("\n\n\t\t!!!! ERROR :--> RECORD NOT FOUND !");


printf("\n\n\t\tWant to enter another search (Y/N) :--> ");
fflush(stdin);
another=getchar();
}
}


int main()
{
 FILE * MY_FILE_SECTION_A;
 Student s;
int option;
char another;

if((MY_FILE_SECTION_A=fopen("student_management_system.txt","rb+"))==NULL)
{
    if((MY_FILE_SECTION_A=fopen("student_management_system","wb+"))==NULL)
       {
           printf(" :--> can't open file");
           return 0;
       }
}

printHead();
  printf(" \n \n \n CREATED BY : \n" );
	printf(" \n -------------------------------\n ");
	printf("| HUSSAIN GHAZALI  | |17k-3900| \n | HASSAN SHAKEEL   | |17k-3857| \n | ZUHAIR WAHEED    | |17k-3706| \n | SHAYAN NOOR KHAN | |17k-3744|");
      printf(" \n ------------------------------- \n");
printf("\n\t\tpress any key to continue");
getch();

while(1)
{
    printHead();
    printf("\n\t");
    printChar('-',64);

    printf("\n\n\t\t:--> 1. ADD Student");
    printf("\n\n\t\t:--> 2. DELETE Student");
    printf("\n\n\t\t:--> 3. MODIFY Student");
    printf("\n\n\t\t:--> 4. DISPLAY Student LIST");
    printf("\n\n\t\t:--> 5. Search Record");
    printf("\n\n\t\t:--> 0. EXIT");

    printf("\n\n\t\tEnter Your Option :--> ");
    scanf("%d",&option);

    switch(option)
    {
        case 0: return 1;
                break;
        case 1: ADD_RECORD(MY_FILE_SECTION_A);
                break;
        case 2: MY_FILE_SECTION_A=DELETE_RECORD(MY_FILE_SECTION_A);
                break;
        case 3: MODIFY_RECORD(MY_FILE_SECTION_A);
                break;
        case 4: DISPLAY_RECORD(MY_FILE_SECTION_A);
                break;
        case 5: SEARCH_RECORD(MY_FILE_SECTION_A);
                break;
        default: printf("\n\t :--> You Pressed wrong key");
                  printf("\n\t :--> Program CRASHED");
                  getch();
                  exit(0);

    }
}
return 1;
}


  
