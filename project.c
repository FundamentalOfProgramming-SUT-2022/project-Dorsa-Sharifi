/*Name:Dorsa Sharifi Ghombavani
  Student ID:401170604*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <direct.h>
#include <stdbool.h>
#define order1 "createfile --file <filename & address>"

//Main Functions
void Createfile(char *);
void insertstr(char *,int );

//Auxiliary Functions
int Counting_Directories(char *);
int Directory_Existance(const char * );
void makingdirectories(char *,int );
char *REPLACE(char *);

//body of functions
int Counting_Directories(char *a){
    int counter=0;
    char *path2=(char *)malloc(sizeof(char)*10000);
    char *path3=(char *)malloc(sizeof(char)*10000);
    strcpy(path2,a);
    path3=strtok(path2,"/");
    while(path3!=NULL){
        counter++;
        path3=strtok(NULL,"/");
    }
    return counter;
}

int Directory_Existance(const char *path){
    struct stat a;
    stat(path, &a);
    return S_ISDIR(a.st_mode);
}

void Createfile(char *a){
    char *filename=strtok(a,"\"");
    if(access(filename,F_OK)==0){
        printf("Oops!The file already exists.\n");
    }
    else{
        FILE* file=fopen(filename,"w");
        fclose(file);
        printf("Congrats!Your file: %s is created.\n",filename);
    }
}

void makingdirectories(char *b,int B){
    char *PATHR=(char *)malloc(sizeof(char)*10000);
    int i=0;
    char *way;
    char *previous=NULL;
    struct stat stats;
    strcpy(PATHR,b);
    way=strtok(PATHR,"/");//removing "/ from the begining of the remained string
    way=strtok(NULL,"/");
    while(way!=NULL && i<B-1){
        if(strcmp(way,"root")!=0){
            if(i==B-2){
                Createfile(way);
            }
            else{
                stat(way,&stats);
                if(S_ISDIR(stats.st_mode)){
                    
                }
                else{
                    mkdir(way);
                    printf("The Directory:%s is made\n",way);
                }
            }    
        }    
        chdir(way);
        way=strtok(NULL,"/");
        i++;   
    }
}

char *REPLACE(char *inputstring){
    int strsize=strlen(inputstring);
    int i=0;
    int quotecontrol=0;
    int bbncontroller=0;
    int bncontroller=0;
    //counting how many bbns and bns we have 
    while(i<strsize ){
        if((strstr(&inputstring[i],"\\")==&inputstring[i]) && (strstr(&inputstring[i+1],"\\")==&inputstring[i+1]) && (strstr(&inputstring[i+2],"n")==&inputstring[i+2])){
          bbncontroller++;//every bbn is 3 char which becomes 2 in new size
          i=i+3;
        }
        else if((strstr(&inputstring[i],"\\")==&inputstring[i]) && (strstr(&inputstring[i+1],"n")==&inputstring[i+1]) && (strstr(&inputstring[i-1],"\\")==NULL) ){
          i=i+2;
          bncontroller++;//every newline is one char but it's counted twice in initial string 
        }
        else{
          i++;
        }  
    }
    for (int i=0;i<strsize;i++){
        if((strstr(&inputstring[0],"\"")==&inputstring[0]) && ((strstr(&inputstring[strsize-2],"\"")==&inputstring[strsize-2]))){
            strcpy(&inputstring[i],&inputstring[i+1]);
            quotecontrol++;
            
        }
        else{
            break;
        }
    }
    if(quotecontrol!=0){
        strsize-=2;
    }    
    
    int difference=(-1)*(bbncontroller+bncontroller);//-1 because of reduction
    int newsize=strsize-difference;
    inputstring[strsize]='\0';
    char *newstr=(char *)malloc((newsize+1)*sizeof(char));//a string with new size
    int k=0;
    int j=0;
    //going through the loop again for replacement in a new char *
    while(k<strsize-1){
        if((strstr(&inputstring[k],"\\")==&inputstring[k]) && (strstr(&inputstring[k+1],"\\")==&inputstring[k+1]) && (strstr(&inputstring[k+2],"n")==&inputstring[k+2])){
            strcpy(&newstr[j],&inputstring[k]);
            strcpy(&newstr[j+1],&inputstring[k+2]);
            j+=2;
            k+=3;
        }
        else if((strstr(&inputstring[k],"\\")==&inputstring[k]) && (strstr(&inputstring[k+1],"n")==&inputstring[k+1]) && (strstr(&inputstring[k-1],"\\")!="\\") ){
            strcpy(&newstr[j],"\n");
            j++;
            k+=2;
        }
        else{
            strcpy(&newstr[j],&inputstring[k]);
            j++;
            k++;
        }
    }
    newstr[j]='\0';
    return newstr;;
}

void insertstr(char *pathR,int counter){
    int i=1;
    int a;
    char thepath[1024];
    char *filename=(char *)malloc(1024*sizeof(char));
    char *masir=(char *)malloc(1024*sizeof(char));
    char *way=(char *)malloc(1024*sizeof(char));
    char *way2=(char *)malloc(1024*sizeof(char));
    char *rest=(char *)malloc(1024*sizeof(char));
    char *text=(char *)malloc(1024*sizeof(char));
    FILE *my_file;
    FILE *auxiliary;
    strcpy(masir,pathR);
    strcpy(way,pathR);
    filename=strtok(masir,"-");//reaches to --str
    way2=strtok(way,"/");
    //checking if the directories(not the file) exist or what 
    while(way2!= NULL && i<counter){
        a=Directory_Existance(way2);
        if(a==0){
            printf("Oops!The directory: %s does not exist.\n",way2);
            break;
        }
        chdir(way2);
        //remember that in the last round way2 reaches to the file
        way2=strtok(NULL,"/");
        i++;
    }
    char buffer[1024];
    _getcwd(buffer,1024);
    strcat(buffer,"\\auxiliary.txt");
    chdir("E:/root");
    rest=strtok(way2,"-");//filename
    my_file=fopen(filename,"r");
    if(my_file==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        rest=strtok(NULL," ");//--strtok
        rest=strtok(NULL,"-");//inserttext;
        text=REPLACE(rest);
        rest=strtok(NULL," ");//--pos
        int givenline=atoll(strtok(NULL,":"));
        int givenposition=atoll(strtok(NULL," "));
        int linecounter=1;
        int characters = 0;//Note : the indices are started from 0 according to document
        char line;
        int c;
        //counting present lines in the file
        do{
            line=fgetc(my_file);
            if(line=='\n'){
                linecounter++;
            }
        }while(line!=EOF);
        //counting present letters in the file 
        rewind(my_file);
        do{
            c = fgetc(my_file);
            characters++;    
        }while(c!=EOF);
        rewind(my_file);
        auxiliary=fopen(buffer,"w");
        //copying current data to a new file
        int controller=0;
        for(int i=1;i<=givenline;i++){
            int letterreplace=0;
            while((c=fgetc(my_file))!='\n'){
                if(letterreplace==givenposition && i==givenline){
                    controller=1;
                    break;
                }
                fputc(c,auxiliary);
                letterreplace++;
            }
            if(controller==0){
                fprintf(auxiliary,"\n");
            }    
        }
        fputs(text,auxiliary);
        fputc(c,auxiliary);
        while((c=fgetc(my_file))!=EOF){
            fputc(c,auxiliary);
        }
        fclose(my_file);
        fclose(auxiliary);
        my_file=fopen(filename,"w");
        auxiliary=fopen(buffer,"r");
        while((c=fgetc(auxiliary))!=EOF){
            fprintf(my_file,"%c",c);
        }
        printf("Your text is appended to the file successfully!\n");
        fclose(my_file);
        fclose(auxiliary);
        remove(buffer);
        free(filename);
        free(masir);
        free(way);
        free(way2);
        free(rest);
        free(text);
    }          
}

int main(){
    char *path=(char *)malloc(sizeof(char)*10000);
    char *command;
    char *command2;
    char *pathR;
    char *pathC;
    int counter=0;
    char *root;
    mkdir("E:/root");
    while (1){
        chdir("E:/root");
        gets(path);
        command=strtok(path," ");//recognizing the user's command
        command2=strtok(NULL," ");//recognizing whether it has --file or what
        if((strcmp(command,"createfile")==0) && (strcmp(command2,"--file")==0)){
            pathR=strtok(NULL,"\n");//getting the remain of path
            counter=Counting_Directories(pathR);
            makingdirectories(pathR,counter);
        }
        else if((strcmp(command,"insertstr")==0) && (strcmp(command2,"--file")== 0)){
            pathR=strtok(NULL,"/");//getting the root
            pathR=strtok(NULL,"\n");//getting the remain of path
            counter=Counting_Directories(pathR);
            insertstr(pathR,counter);
        }        
    }
}