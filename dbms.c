//filehandling
#include<stdio.h>
#include<stdlib.h>
struct student
{
 int sid;
 char sname[20];
 float attendance;
}stud;

//Insert
void insert()
{
 FILE *fp;
 fp = fopen("Data", "a");
 printf("Enter sid : ");
 scanf("%d", &stud.sid);
 printf("Enter sname : ");
 scanf("%s",stud.sname);
 printf("Enter Attendance : ");
 scanf("%f", &stud.attendance);
 fwrite(&stud, sizeof(stud), 1, fp);
 fclose(fp);
}

//Display
void disp()
{
 FILE *fp1;
 fp1 = fopen("Data", "r");
 printf("\nSID\tSNAME\t\tATTENDANCE\n\n");
 while (fread(&stud, sizeof(stud), 1, fp1))
 printf("%d\t%s\t\t%.2f\n", stud.sid, stud.sname, stud.attendance);
 fclose(fp1);
}

//Check if sid is available
int avlsid(int sid)
{
 FILE *fp;
 int c = 0;
 fp = fopen("Data", "r");
 while (!feof(fp))
 {
  fread(&stud, sizeof(stud), 1, fp);

  if (sid == stud.sid)
  {
   fclose(fp);
   return 1;
  }
 }
 fclose(fp);
 return 0;
}

//Search
void search()
{
 FILE *fp2;
 int r, s, avl;
 printf("Enter sid to search  : ");
 scanf("%d", &r);
 avl = avlsid(r);
 if (avl == 0)
  printf("SID %d is not available!!\n",r);
 else
 {
  fp2 = fopen("Data", "r");
  while (fread(&stud, sizeof(stud), 1, fp2))
  {
   s = stud.sid;
   if (s == r)
   {
    printf("\nsid = %d", stud.sid);
    printf("\nsname = %s", stud.sname);
    printf("\nattendance = %.2f\n", stud.attendance);
   }
  }
  fclose(fp2);
 }
}

//Delete
void deletefile()
{
 FILE *fpo;
 FILE *fpt;
 int r, s;
 printf("Enter sid to delete : ");
 scanf("%d", &r);
 if (avlsid(r) == 0)
  printf("sid %d is not available!!!\n", r);
 else
 {
  fpo = fopen("Data", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   s = stud.sid;
   if (s != r)
    fwrite(&stud, sizeof(stud), 1, fpt);
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Data", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&stud, sizeof(stud), 1, fpt))
   fwrite(&stud, sizeof(stud), 1, fpo);
  printf("\nDATA DELETED!!\n");
  fclose(fpo);
  fclose(fpt);
 }
}

//Update
void update()
{
 int avl;
 FILE *fpt;
 FILE *fpo;
 int s, r, ch;
 printf("Enter sid to update : ");
 scanf("%d", &r);
 avl = avlsid(r);
 if (avl == 0)
 {
  printf("sid %d is not Available!!!\n", r);
 }
 else
 {
  fpo = fopen("Data", "r");
  fpt = fopen("TempFile", "w");
  while (fread(&stud, sizeof(stud), 1, fpo))
  {
   s = stud.sid;
   if (s != r)
    fwrite(&stud, sizeof(stud), 1, fpt);
   else
   {
    printf("\n1. Update SName of %d", r);
    printf("\n2. Update Attendance of %d", r);
    printf("\n3. Update both SName and Attendance of %d\n", r);
    printf("\nEnter choice : ");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
     printf("Enter SName : ");
     scanf("%s",stud.sname);
     break;
    case 2:
     printf("Enter Attendance : ");
     scanf("%f", &stud.attendance);
     break;
    case 3:
     printf("Enter SName : ");
     scanf("%s",stud.sname);
     printf("Enter Attendance : ");
     scanf("%f", &stud.attendance);
     break;
    default:
     printf("Invalid Selection!!");
     break;
    }
    fwrite(&stud, sizeof(stud), 1, fpt);
   }
  }
  fclose(fpo);
  fclose(fpt);
  fpo = fopen("Data", "w");
  fpt = fopen("TempFile", "r");
  while (fread(&stud, sizeof(stud), 1, fpt))
  {
   fwrite(&stud, sizeof(stud), 1, fpo);
  }
  fclose(fpo);
  fclose(fpt);
  printf("\nDATA UPDATED!!\n");
 }
}

//Check if file is empty
int empty()
{
 int c = 0;
 FILE *fp;
 fp = fopen("Data", "r");
 while (fread(&stud, sizeof(stud), 1, fp))
  c = 1;
 fclose(fp);
 return c;
}

//MAIN
void main()
{
 int ch, emp;
 do
 {
  printf("\n<===== Select =====>\n");
  printf("\n1. INSERT\n2. DISPLAY\n3. SEARCH");
  printf("\n4. DELETE\n5. UPDATE\n6. Exit\n");
  printf("\nEnter choice : ");
  scanf("%d", &ch);
  printf("\n");
  switch (ch)
  {
  case 1:
   insert();
   break;
  case 2:
   emp = empty();
   if (emp == 0)
    printf("\nThe file is EMPTY\n");
   else
    disp();
   break;
  case 3:
   search();
   break;
  case 4:
   deletefile();
   break;
  case 5:
   update();
   break;
  case 6:
   exit(1);
   break;
  default:
   printf("\nINVALID CHOICE!!!\n");
   break;
  }
 } while (ch != 6);
}