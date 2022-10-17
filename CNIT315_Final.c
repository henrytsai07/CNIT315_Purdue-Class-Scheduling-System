
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>



typedef struct {
    unsigned char *buffer;
    size_t len;
    size_t buflen;
} get_request;

#define CHUNK_SIZE 2048

#define MAX 256
 
//prototypes
void menu();
void add(int index);
void search();
void DisplayTime();
void DisplayClass();
void delete();
void showClass();

 
 
typedef struct
  {
   char classnum[10];
   char ID[10];
   char time[10];
   char professor_f[20], professor_l[20];
   char desc[30];
  } class;
class classn[10];


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    size_t realsize = size * nmemb; 
    get_request *req = (get_request *) userdata;

    //printf("receive chunk of %zu bytes\n", realsize);

    while (req->buflen < req->len + realsize + 1)
    {
        req->buffer = realloc(req->buffer, req->buflen + CHUNK_SIZE);
        req->buflen += CHUNK_SIZE;
    }
    memcpy(&req->buffer[req->len], ptr, realsize);
    req->len += realsize;
    req->buffer[req->len] = 0;

    return realsize;
}


int main(int argc, char **argv) {
    int i;
  int i2;
   int index = 0;
  int choice = 0;
  int result = 1;
  int result2 = 1;
  char usernameinput[15];
  char userpassword[15];
  char username[5][15] = {"test", "a", "faculty"};
  char password[5][15] = {"test", "a", "password"};
  int len = sizeof(username);
  printf("\n\n Login Menu");
  printf("\n ----------");
  printf("\n Please Enter Your Username: ");
  scanf("%s", usernameinput);
  printf("\n Please Enter Your Password: ");
  scanf("%s", userpassword);
 
  // comparing strings str1 and str3
  for (i = 0; i < len; i++)
  {
   result = strcmp(usernameinput, username[i]);
   int x = i;
   result2 = strcmp(userpassword, password[x]);
   if (result == 0)
   {
       if (result2 == 0)
       {
           printf("\nLogin succeeded.");
   do
   {
       printf("\n\n\n Choose a term:");
       printf("\n ----------------------");
       printf("\n   1. Spring");
       printf("\n   2. Summer");
       printf("\n   3. Fall");
       printf("\n   4. EXIT");
       printf("\n\n Enter Your Choice: ");
       scanf("%d", &choice);
       switch (choice)
       {
       case 1:
           menu();
           break;
       case 2:
            menu();

           printf("\nYOU SELECTED OPTION 2\n");
           break;
       case 3:
            menu();
           printf("\nYOU SELECTED OPTION 3\n");
           break;
       case 4:
            menu();
           printf("\nYOU SELECTED OPTION 4\n");
           break;
       default:
           printf("\nINVALID SELECTION...Please try again");
       }
   } while (choice != 4);
       }
       else
       {
           result2 = 0;
       }
   }
   else
   {
       result = 1;
   }
  }
  if (result == 1 || result2 == 1)
  {
   printf("\nIncorrect Username or Password entered.\n\n");
  }
  strcpy(classn[0].classnum, "CNIT315");
 
}
 
void menu(){
   int option = 0;
   int index = 0;
   do{
       printf("\n\n *****Options *****");
       printf("\n 1: Add a class");
       printf("\n 2: Drop a class");
       printf("\n 3: Search for a class");
       printf("\n 4: Show the list of classes");
       printf("\n 5: Save schedule");
       printf("\n 6: Quit program");
 
       printf("\n\n Enter your option : ");
       scanf("%d", &option);
       switch (option)
       {
       case 1:
           printf("\nPlease enter the following information: \n");
           add(0);
           printf("%s", classn[index].classnum);
           index++;
           break;
       case 2:
           printf("\nYOU SELECTED OPTION 2\n");
           //code to drop a class
           delete();
           break;
       case 3:
           printf("\nPlease enter the following information:\n");
           //code to search a class
           search();
          
           break;
        case 4:
            showClass();
            break;

       case 5:
           DisplayClass();
           printf("\nSchedule saved. \n");
           DisplayTime();
           break;
       case 6:
           printf("\nPROGRAM END\n");
           exit(0);
       default:
           printf("\nINVALID SELECTION...Please try again\n");
       }
   }while (option != 5);
}
 
void add(int index)
{
   char classnum[10];
   char time[10];
   char professor_f[20], professor_l[20];
   char desc[30];
   char ID[10];
  
   FILE *fptr;                         //writes to txt file but can only save one class(class name, time, professor, desc) per program run
   fptr = fopen("courses.txt","a");
   if(fptr == NULL)
   {
       printf("Error!");
       exit(1);
   }
 
   printf("Enter the Class Title: ");
   scanf("%s", &classnum);
   printf("Enter the Class ID (5 numbers): ");
   scanf("%s", &ID);
   printf("Enter the Credit Hours (3.00 Format): ");
   scanf("%s", &time);
   printf("Enter the Professor: ");
   scanf("%s%s", professor_f, professor_l);    //changed professor tp first and last name
   
  
   fprintf(fptr, "%s ", classnum); //prints to the txt file
    fprintf(fptr, "%s ", ID);
   fprintf(fptr, "%s ", time);
   fprintf(fptr, "%s %s ", professor_f, professor_l);
   fprintf(fptr, "%s \n", desc);
   fclose(fptr);
 
   strcpy(classn[index].classnum, classnum);
    strcpy(classn[index].ID, ID);

   strcpy(classn[index].time, time);
   strcpy(classn[index].professor_f, professor_f);
   strcpy(classn[index].professor_l, professor_l);
   strcpy(classn[index].desc, desc);
 
}
 
void delete(){
 
       int lno, ctr = 0;
       char ch;
       FILE *fptr1, *fptr2;
       char fname[MAX] = "courses.txt";
       char str[MAX], temp[] = "temp.txt";
       printf("\n\n Delete a specific line from a file :\n");
       printf("-----------------------------------------\n");
  
       fptr1 = fopen(fname, "r");
       if (!fptr1)
       {
               printf(" File not found or unable to open the input file!!\n");
               exit(0);
       }
       fptr2 = fopen(temp, "w"); // open the temporary file in write mode
       if (!fptr2)
       {
               printf("Unable to open a temporary file to write!!\n");
               fclose(fptr1);
               exit(0);
       }
       printf(" Input the line you want to remove : ");
       scanf("%d", &lno);
 
       // copy all contents to the temporary file except the specific line
       while (!feof(fptr1))
       {
           strcpy(str, "\0");
           fgets(str, MAX, fptr1);
           if (!feof(fptr1))
           {
               ctr++;
               /* skip the line at given line number */
               if (ctr != lno)
               {
                   fprintf(fptr2, "%s", str);
               }
           }
       }
       fclose(fptr1);
       fclose(fptr2);
       remove(fname);          // remove the original file
       rename(temp, fname);    // rename the temporary file to original name
}
 
void search()
{
       int lno, ctr = 0;
       char ch;
       FILE *fptr1, *fptr2;
       FILE *fptr;
       char ch2;
       char fname[MAX] = "courses.txt";
       char str[MAX], temp[] = "temp.txt";
       printf("\n\n Search a specific line from a file :\n");
       printf("-----------------------------------------\n");
  
       fptr1 = fopen(fname, "r");
       if (!fptr1)
       {
               printf(" File not found or unable to open the input file!!\n");
               exit(0);
       }
       fptr2 = fopen(temp, "w"); // open the temporary file in write mode
       if (!fptr2)
       {
               printf("Unable to open a temporary file to write!!\n");
               fclose(fptr1);
               exit(0);
       }
       printf(" Input the line you want to search : ");
       scanf("%d", &lno);
 
       // copy all contents to the temporary file except the specific line
       while (!feof(fptr1))
       {
           strcpy(str, "\0");
           fgets(str, MAX, fptr1);
           if (!feof(fptr1))
           {
               ctr++;
               /* skip the line at given line number */
               if (ctr == lno)
               {
                   fprintf(fptr2, "%s", str);
               }
           }
       }
       fclose(fptr1);
       fclose(fptr2);
   fptr = fopen("temp.txt", "r");
  
       if (fptr == NULL)
   {
   printf("Cannot open file \n");
   exit(0);
   }
   printf("\n");
   ch = fgetc(fptr);
   while (ch2 != EOF)
   {
   printf ("%c", ch2);
   ch2 = fgetc(fptr);
   }
   fclose(fptr);
}
      
 
      
 
  
void DisplayClass(){
FILE *fptr;
char ch;
fptr = fopen("courses.txt", "r");
   if (fptr == NULL)
 {
  printf("Cannot open file \n");
  exit(0);
 }
 ch = fgetc(fptr);
 printf("\n");
 printf("Title\tID\tCredits\tProfessor\n");
 printf("==============================\n");
 while (ch != EOF)
 {
  printf ("%c", ch);
  ch = fgetc(fptr);
 }
fclose(fptr);
}
 
void DisplayTime()
{
  
   struct tm* ptr;
   time_t t;
   t = time(NULL);
   ptr = localtime(&t);
   printf("%s", asctime(ptr));
}
void showClass()
{

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    char* CNIT = "https://api.purdue.io/odata/Courses?$filter=Subject/Abbreviation%20eq%20%27CNIT%27%20and%20Number%20le%20%2719999%27&$orderby=Number%20asc";
    char* CS = "https://api.purdue.io/odata/Courses?$filter=Subject/Abbreviation%20eq%20%27CS%27%20and%20Number%20le%20%2719999%27&$orderby=Number%20asc";
    char* CGT = "https://api.purdue.io/odata/Courses?$filter=Subject/Abbreviation%20eq%20%27CGT%27%20and%20Number%20le%20%2719999%27&$orderby=Number%20asc";


    get_request req = {.buffer = NULL, .len = 0, .buflen = 0};
    

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, CNIT);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "length: 20");
        headers = curl_slist_append(headers, "numbers: true");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        req.buffer = malloc(CHUNK_SIZE);
        req.buflen = CHUNK_SIZE;

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&req);

        res = curl_easy_perform(curl);
        // printf("Result = %u\n",res);

        // printf("Total received bytes: %zu\n", req.len);
        char *token = strtok(req.buffer, ",");
   // loop through the string to extract all other tokens
        while( token != NULL ) {
            if(strstr(token, "Number") != NULL){
                printf( "\n %s\n", token ); //printing each token

            }
            if(strstr(token, "Title") != NULL){
                printf( " %s\n", token ); //printing each token
            }
            // if(strstr(token, "Description") != NULL){
            //     printf( " %s\n", token ); //printing each token
            // }
            if(strstr(token, "CreditHours") != NULL){
                printf( " %s\n", token ); //printing each token
                printf("\n");

            }
        

  
            token = strtok(NULL, ",");
        }
        
        printf("Received data:\n%s\n", req.buffer);
        free(req.buffer);        
    }

    curl_easy_cleanup(curl);
}
