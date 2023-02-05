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
#include <windows.h>
#include <ctype.h>
#include <sys/types.h>

//Main Functions
void Createfile(char *);
void insertstr(char *);
void cat(char *);
void copy(char *);
void removestr(char *);
void paste(char *);
void undo(char *);
void grepempty(char *,int );
void autoindent(char *);
void findcount(char *,char *,char *);
void findat(char *,char *,char *);
void findbyword(char *,char *);
void findall(char *,char *);
void find(char *);
void treeminus1(char *,const int);
void tree(char *,int ,int,int);


//Auxiliary Functions
char *CheckQuote(char *);
char *CheckQuote2(char *);
char *CheckQuote3(char *);
char *CheckQuote4(char *);
int Counting_Directories(char *);
int Directory_Existance(const char * );
void makingdirectories(char *,int );
char *REPLACE(char *);
void BackupFile(char *);

//global variables
int numberingrep=1;

//body of functions
char *CheckQuote(char *command){
    char *address=(char *)malloc(1024*sizeof(char));
    char *checkquote=(char *)malloc(1024*sizeof(char));
    for (int i=0;i<strlen(command);i++){//getting the address
        if((strstr(&command[i],"-")==&command[i]) && (strstr(&command[i+1],"-")==&command[i+1]) && (strstr(&command[i+2],"p")==&command[i+2]) && (strstr(&command[i+3],"o")==&command[i+3]) && (strstr(&command[i+4],"s")==&command[i+4])){
            address[i]='\0';
            break;
        }
        else{
            strcpy(&address[i],&command[i]);
        }
    }
    return address;
}

char *CheckQuote2(char *command){
    char *address=(char *)malloc(1024*sizeof(char));
    char *checkquote=(char *)malloc(1024*sizeof(char));
    for (int i=0;i<strlen(command);i++){//getting the address
        if((strstr(&command[i],"-")==&command[i]) && (strstr(&command[i+1],"-")==&command[i+1]) && (strstr(&command[i+2],"s")==&command[i+2]) && (strstr(&command[i+3],"t")==&command[i+3]) && (strstr(&command[i+4],"r")==&command[i+4])){
            address[i]='\0';
            break;
        }
        else{
            strcpy(&address[i],&command[i]);
        }
    }
    strcpy(checkquote,address);
    if((checkquote=strtok(checkquote,"\""))!=NULL){
        strcpy(address,checkquote);
    }
    return address;
}

char *CheckQuote3(char *command){
    char *address=(char *)malloc(1024*sizeof(char));
    char *checkquote=(char *)malloc(1024*sizeof(char));
    strcpy(address,command);
    checkquote=strstr(command,"\"");
    if(checkquote==NULL){
        address=strtok(address," ");
    }
    else{
        address=CheckQuote2(address);
    }
    return address;
}

char *CheckQuote4(char *command){
    char *addrress=(char *)malloc(1024*sizeof(char));
    char *checkquote=(char *)malloc(1024*sizeof(char));
    strcpy(addrress,command);
    for (int i=0;i<strlen(addrress);i++){
        if((strstr(&addrress[i],"-")==&addrress[i]) && (strstr(&addrress[i+1],"-")==&addrress[i+1]) && (strstr(&addrress[i+2],"f")==&addrress[i+2]) &&
        (strstr(&addrress[i+3],"i")==&addrress[i+3]) && (strstr(&addrress[i+4],"l")==&addrress[i+4]) && (strstr(&addrress[i+5],"e")==&addrress[i+5])){
            checkquote[i]='\0';
            break;
        }
        else{
            strcpy(&checkquote[i],&addrress[i]);
        }
    }
    checkquote=CheckQuote2(checkquote);
    return checkquote;
}    
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
    return newstr;
}

void insertstr(char *pathR){
    int i=1;
    int a;
    char thepath[1024];
    char buffer[1024];
    char *filename=(char *)malloc(1024*sizeof(char));
    char *masir=(char *)malloc(1024*sizeof(char));
    char *way=(char *)malloc(1024*sizeof(char));
    char *way2=(char *)malloc(1024*sizeof(char));
    char *rest=(char *)malloc(1024*sizeof(char));
    char *text=(char *)malloc(1024*sizeof(char));
    char *backup=(char *)malloc(1024*sizeof(char));
    FILE *my_file;
    FILE *auxiliary;
    strcpy(masir,pathR);
    strcpy(way,pathR);
    filename=CheckQuote2(pathR);
    strcpy(backup,filename);
    _getcwd(buffer,1024);
    strcat(buffer,"\\auxiliary.txt");//making a temp file 
    chdir("E:");
    my_file=fopen(filename,"r");
    if(my_file==NULL){
        printf("Oops!Unable to open the directories/file.\n");
    }
    else{
        BackupFile(backup);
        masir=strstr(masir,"--str");
        way2=strtok(masir," ");//inserttext;
        way2=strtok(NULL,"\n");
        way2=CheckQuote(way2);
        text=REPLACE(way2);
        rest=strstr(way,"--pos");
        rest=strtok(rest," ");//--pos
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

void cat(char *filename){
    char *backup=(char *)malloc(1024*sizeof(char));
    FILE *my_file;
    char c;
    filename=CheckQuote2(filename);
    strcpy(backup,filename);
    my_file=fopen(filename,"r");
    if(my_file==NULL){
        printf("Oops!Unable to open the file.\n");        
    }
    else{
        BackupFile(backup);
        printf("The data inside file is displayed below:\n");
        while((c=fgetc(my_file))!=EOF){
            printf("%c",c);
        }
    }
    fclose(my_file);
}

void removestr(char *command){
    int c;
    int j=1;
    int controller=0;
    int number;
    int givenline;
    int givenposition;
    int linecounter=0;
    char *address=(char *)malloc(1024*sizeof(char));
    char *rest=(char *)malloc(1024*sizeof(char));
    char *pos=(char *)malloc(1024*sizeof(char));
    char *pos2=(char *)malloc(1024*sizeof(char));
    char *backup=(char *)malloc(1024*sizeof(char));
    FILE *my_file;
    FILE *tmp_file;
    address=CheckQuote(command);
    strcpy(backup,address);
    rest=strstr(command,"--pos");
    pos=strtok(rest," ");//spliting --pos
    pos=strtok(NULL,":");
    givenline=atoll(pos);
    pos=strtok(NULL," ");
    givenposition=atoll(pos);
    pos=strtok(NULL," ");//spliting --size
    pos=strtok(NULL," ");
    number=atoll(pos);
    pos2=strtok(NULL,"\n");//spliting direction
    my_file=fopen(address,"r");
    tmp_file=fopen("E:/root/temp.txt","w");
    if(my_file==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        BackupFile(backup);
        if(strcmp(pos2,"-f")==0){ //forward
            for(int k=1;k<=givenline;k++){
                int charactercounter=0;
                while((c=fgetc(my_file))!='\n'){
                    if(charactercounter==givenposition && k==givenline){
                        controller=1;
                        break;
                    }
                    fputc(c,tmp_file);
                    charactercounter++;
                }
                if(controller==0){
                    fprintf(tmp_file,"\n");
                }
            }
            fseek(my_file,number-1,SEEK_CUR);
            while((c=fgetc(my_file))!=EOF){
                fputc(c,tmp_file);
            }
        }
        else if(strcmp(pos2,"-b")==0){//backward
            for(int p=1;p<=givenline;p++){
                int charactercounter2=0;
                while((c=fgetc(my_file))!='\n'){
                    if(charactercounter2==givenposition && p==givenline){
                        controller=1;
                        break;
                    }
                    fputc(c,tmp_file);
                    charactercounter2++;
                }
                if(controller==0){
                    fprintf(tmp_file,"\n");
                }
            }
            fseek(tmp_file,-1*(number),SEEK_CUR);
            fputc(c,tmp_file);
            while((c=fgetc(my_file))!=EOF){
                fputc(c,tmp_file);
            }   
        }
        fclose(tmp_file);
        fclose(my_file);
        my_file=fopen(address,"w");
        tmp_file=fopen("E:/root/temp.txt","r");
        while((c=fgetc(tmp_file))!=EOF){
            fprintf(my_file,"%c",c);
        }
        printf("The chosen substring is omitted from the file.\n");
        fclose(my_file);
        fclose(tmp_file);
        remove("E:/root/temp.txt");
        free(address);
        free(rest);
        free(pos);
        free(pos2);
    }
    
}

void copy(char *path){
    char *pos=(char *)malloc(5);
    char *pos2;
    char *address=(char *)malloc(1024*sizeof(char));
    char *rest=(char *)malloc(1024*sizeof(char));
    char *direction=(char *)malloc(2);
    char *finalanswer=(char *)malloc(1024*sizeof(char));
    char *backup=(char *)malloc(1024*sizeof(char));
    long long length;
    int c;
    int j=0;
    int linecounter=1;
    long long givenline;
    long long givenposition;
    long long number;
    char savedata[1024];
    FILE *my_file;
    address=CheckQuote(path);
    strcpy(backup,address);
    rest=strstr(path,"--pos");
    pos=strtok(rest," ");//removing --pos
    pos=strtok(NULL,":");//line 
    givenline=atoll(pos);
    pos2=strtok(NULL," ");//char index
    givenposition=atoll(pos2);
    pos2=strtok(NULL," ");//removing -size
    pos2=strtok(NULL," ");
    number=atoll(pos2);
    direction=strtok(NULL,"\n");
    my_file=fopen(address,"r");
    if(my_file==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        BackupFile(backup);
        if(strcmp(direction,"-f")==0){
            for(int i=1;i<=givenline;i++){//passing the file untill reaching the given position
                int charactercounter=0;
                while((c=fgetc(my_file))!='\n'){
                    if(i==givenline && charactercounter==givenposition){
                        finalanswer[0]=c;
                        break;
                    }
                    charactercounter++;
                }
            }
            for(int j=1;j<number;j++){//saving the letters which are gonna be copied
                c=fgetc(my_file);
                finalanswer[j]=c;
            }
            finalanswer[number]='\0';
        }
        else if (strcmp(direction,"-b")==0){
            for(int i=1;i<=givenline;i++){
                int charactercounter2=0;
                while((c=fgetc(my_file))!='\n'){
                    if(i==givenline && charactercounter2==givenposition){
                        finalanswer[number-1]=c;
                        break;
                    }
                    charactercounter2++;
                }
            }
            fseek(my_file,-1*(number+1),SEEK_CUR);
            for (int j=0;j<number;j++){
                c=fgetc(my_file);
                finalanswer[j]=c;
            }
            finalanswer[number]='\0';
        }  
        length=strlen(finalanswer)+1;
        HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, length);//copying the data to the clipboard
        memcpy(GlobalLock(hMem),finalanswer,length);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem); 
        CloseClipboard();
        free(pos);
        free(pos2);
        free(direction);
    }
}

void paste(char *path){
    char *cut1=(char *)malloc(1024*sizeof(char));
    char *savingdata=(char *)malloc(1024*sizeof(char));
    char *cut2=(char *)malloc(1024*sizeof(char));
    char *cut3=(char *)malloc(1024*sizeof(char));
    char *cut4=(char *)malloc(1024*sizeof(char));
    char *backup=(char *)malloc(1024*sizeof(char));
    OpenClipboard(0);
    HANDLE copieddata=GetClipboardData(CF_TEXT);
    savingdata=(char *)GlobalLock(copieddata);
    strcpy(cut1,path);
    strcpy(cut3,path);
    cut2=CheckQuote(cut1);//getting the address
    strcpy(backup,cut2);
    BackupFile(backup);
    cut3=strstr(cut3," --pos");//getting the pos
    cut4=strcat(cut2," --str ");
    cut4=strcat(cut4,savingdata);
    cut4=strcat(cut4,cut3);
    GlobalUnlock(copieddata);
    CloseClipboard();
    insertstr(cut4);
    free(cut1);
    free(cut3);
}

void BackupFile(char *path){
    char *pathcpy=(char *)malloc(1024*sizeof(char));
    char *pathcpy2=(char *)malloc(1024*sizeof(char));
    char *pathcpy3=(char *)malloc(2048*sizeof(char));
    char add[2048]="Backup-";
    char slash[2048]="/";
    char slash2[2048]={};
    FILE *mainfile;
    FILE *backupfile;
    int c;
    int rest;
    int number;
    int mainlength;
    int namelength;
    path=CheckQuote2(path);
    mainlength=strlen(path);
    strcpy(pathcpy,path);
    strcpy(pathcpy2,path);
    number=Counting_Directories(path);
    pathcpy=strtok(pathcpy,"/");
    for(int i=1;i<number;i++){//getting the name of file
        pathcpy=strtok(NULL,"/");
    }
    namelength=strlen(pathcpy);
    strcat(add,pathcpy);//making the name of hidden file2
    //some operation to get the address without the name of file
    rest=mainlength-namelength;
    for(int i=0;i<rest;i++){
        strcpy(&pathcpy2[i],&pathcpy2[i]);
    }
    pathcpy2[rest]='\0';
    strcat(pathcpy2,add);//address of hidden file
    backupfile=fopen(pathcpy2,"w");
    mainfile=fopen(path,"r");
    rewind(backupfile);
    if(backupfile==NULL){
        printf("Oops!Something wrong happened during Backup Operation.\n");
    }
    else{
        for(int i=0;(c=fgetc(mainfile))!=EOF;i++){
            fputc(c,backupfile);
        }
        fclose(backupfile);
        fclose(mainfile);
        DWORD hiddenfile=GetFileAttributes(pathcpy2);
        SetFileAttributes(pathcpy2,hiddenfile-FILE_ATTRIBUTE_HIDDEN);   
    }
}

void undo(char *path){
    int c;
    int rest;
    int number;
    int mainlength;
    int namelength;
    char add[2048]="Backup-";
    char slash[2048]="/";
    char *pathcpy=(char *)malloc(1024*sizeof(char));
    char *pathcpy2=(char *)malloc(1024*sizeof(char));
    FILE *BackupFile;
    FILE *MainFile;
    path=CheckQuote2(path);
    mainlength=strlen(path);
    strcpy(pathcpy,path);
    strcpy(pathcpy2,path);
    number=Counting_Directories(path);
    pathcpy=strtok(pathcpy,"/");
    for(int i=1;i<number;i++){//getting the name of file
        pathcpy=strtok(NULL,"/");
    }
    namelength=strlen(pathcpy);
    strcat(add,pathcpy);//making the name of hidden file2
    //some operation to get the address without the name of file
    rest=mainlength-namelength;
    for(int i=0;i<rest;i++){
        strcpy(&pathcpy2[i],&pathcpy2[i]);
    }
    pathcpy2[rest]='\0';
    strcat(pathcpy2,add);//address of hidden file
    DWORD hiddenfile=GetFileAttributes(pathcpy2);
    if((hiddenfile & FILE_ATTRIBUTE_HIDDEN)==FILE_ATTRIBUTE_HIDDEN){
        SetFileAttributes(pathcpy2,hiddenfile & ~FILE_ATTRIBUTE_NORMAL);
    }    
    BackupFile=fopen(pathcpy2,"r");
    MainFile=fopen(path,"w");
    if(MainFile!=NULL && BackupFile!=NULL){
        for(int i=0;(c=fgetc(BackupFile))!=EOF;i++){
            fputc(c,MainFile);
        }
        fclose(MainFile);
        fclose(BackupFile);
        remove(pathcpy2);
        printf("Congrats!Your last change is undone.\n");
    }
    else{
        printf("Oops!Something goes wrong while undoing your last change.\n");
    }
}

int AddressCounter(char *cpy2){
    int rootcounter=0;
    for (int i=0;i<strlen(cpy2);i++){
        if((strstr(&cpy2[i],"/")==&cpy2[i]) && (strstr(&cpy2[i+1],"r")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"o")==&cpy2[i+2]) && 
        (strstr(&cpy2[i+3],"o")==&cpy2[i+3]) && (strstr(&cpy2[i+4],"t")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"/")==&cpy2[i+5])){
            rootcounter++;
            i=i+6;
        }
    }
    return rootcounter;
}

void SearchInFile(char *substring,char *address,int sign,int addresscounter,int controller){
    chdir("E:/");
    int eof=0;
    int linecounter=0;
    int findresult=0;
    char substrfound[1024][1024];
    FILE *myfile;
    substring=CheckQuote3(substring);
    BackupFile(address);
    myfile=fopen(address,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file!\n");
    } 
    else{
        if(sign==0){
            while(!feof(myfile) && !ferror(myfile)){
                if(fgets(substrfound[linecounter],1024,myfile)!=NULL){
                    if(strstr(substrfound[linecounter],substring)!=NULL){
                        printf("%s found in %s\n",substrfound[linecounter],address);
                        findresult++;
                    }
                }
                linecounter++;
            }    
        }
        else if(sign==1){
            while(!feof(myfile) && !ferror(myfile)){
                if(fgets(substrfound[linecounter],1024,myfile)!=NULL){
                    if(strstr(substrfound[linecounter],substring)!=NULL){
                        numberingrep++;
                        findresult++;
                    }
                }    
                linecounter++;
            }
            if(controller==addresscounter-1){  
                printf("The number of matches found in all addresses is:%d",numberingrep); 
            } 
        }
        else if(sign==2){
            while(!feof(myfile) && !ferror(myfile)){
                if(fgets(substrfound[linecounter],1024,myfile)!=NULL){
                    if(strstr(substrfound[linecounter],substring)!=NULL){
                        numberingrep++;
                        findresult++;
                    }
                }    
                linecounter++;
            }
            if(findresult!=0){
                printf("Match Found in: %s\n",address);
            }
        }
        else if(findresult==0){
            printf("No Match Found In %s.\n",address);
        }
    }
    fclose(myfile);
}

void grepempty(char *path,int sign){
    int j=0;
    int k=0;
    int addresscounter;
    char *cpy1=(char *)malloc(1024*sizeof(char));
    char *cpy2=(char *)malloc(1024*sizeof(char));
    char *cpy3=(char *)malloc(1024*sizeof(char));
    char *cpy5=(char *)malloc(1024*sizeof(char));
    strcpy(cpy2,path);
    //getting the substring we're looking for & separating its quotations
    for(int i=0;i<strlen(path);i++){
        if((strstr(&path[i],"-")==&path[i]) && (strstr(&path[i+1],"-")==&path[i+1]) && (strstr(&path[i+2],"f")==&path[i+2]) && (strstr(&path[i+3],"i")==&path[i+3]) 
            && (strstr(&path[i+4],"l")==&path[i+4]) && (strstr(&path[i+5],"e")==&path[i+5]) && (strstr(&path[i+6],"s")==&path[i+6])){
            cpy1[i]='\0';
            break;
        }
        else{
            strcpy(&cpy1[i],&path[i]);
        }
    }
    cpy2=strstr(cpy2,"--files");
    cpy2=strtok(cpy2," ");//--files
    cpy2=strtok(NULL,"\n");//string of addresses
    strcpy(cpy3,cpy2);
    addresscounter=AddressCounter(cpy3);
    //finding address of files
    for(int i=0;i<strlen(path);i++){
        j=0;
        if(cpy2[i]=='"'){
            k++;
            cpy5[j]=cpy2[i];
            i++;
            j++;
            while(cpy2[i]!='"'){
                cpy5[j]=cpy2[i];
                j++;
                i++;
            }
            cpy5[j]='\0';
            i++;
            cpy5=CheckQuote2(cpy5);
            SearchInFile(cpy1,cpy5,sign,addresscounter,k); 
        }
        else{
            k++;
            j=0;
            i++;
            cpy5[j]=cpy2[i];
            i++;
            j++;
            while(cpy2[i]!=' ' || cpy2[i]=='\n'){
                cpy5[j]=cpy2[i];
                j++;
                i++;
            }
            cpy5[j]='\0';
            SearchInFile(cpy1,cpy5,sign,addresscounter,k); 
        }
    }
    free(cpy1);
    free(cpy2);
    free(cpy3);
    free(cpy5);
    numberingrep=1;
}
void findcount(char *address,char *pattern,char *wildcard){
    int dashcount=0;
    int notsure=0;
    int k=0;
    char *linebyline=(char *)malloc(1024*sizeof(char));
    char *hey1=(char *)malloc(1024*sizeof(char));
    char *hey2=(char *)malloc(1024*sizeof(char));
    char *hey3=(char *)malloc(1024*sizeof(char));
    bool keep_reading=true;
    FILE *myfile;
    pattern=CheckQuote2(pattern);
    int length=strlen(pattern);
    if(pattern[length-1]==' '){
        pattern[length-1]='\0';
    }
    length=strlen(pattern);
    address=CheckQuote2(address);
    myfile=fopen(address,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        if(strcmp(wildcard,"-count")==0){
            while(!feof(myfile)){
                if(fgets(linebyline,1024,myfile)!=NULL){
                    for(int i=0;i<strlen(linebyline);i++){
                        if(linebyline[i]==pattern[0]){
                            notsure++;
                            k=i+1;
                            for(int j=1;j<length;j++){
                                if(linebyline[k]==pattern[j]){
                                    notsure++;
                                    k++;
                                }
                            }
                            if(notsure==length){
                                dashcount++;
                            }
                            notsure=0;
                        }
                    }
                }
            }
            printf("The number of matches is:%d\n",dashcount);
        }
        fclose(myfile);
    }
}

void findat(char *address,char *pattern,char *wildcard){
    int e=0;
    int k=0;
    int dashat=0;
    int notsure=0;
    int position[1024];
    char *linebyline=(char *)malloc(1024*sizeof(char));
    wildcard=strtok(wildcard," ");
    wildcard=strtok(NULL,"\n");
    long long int pos=atoll(wildcard);
    FILE *myfile;
    pattern=CheckQuote2(pattern);
    int length=strlen(pattern);
    if(pattern[length-1]==' '){
        pattern[length-1]='\0';
    }
    length=strlen(pattern);
    address=CheckQuote2(address);
    myfile=fopen(address,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        while(!feof(myfile)){
            if(fgets(linebyline,1024,myfile)!=NULL){
                for(int i=0;i<strlen(linebyline);i++){
                    if(linebyline[i]==pattern[0]){
                        notsure++;
                        k=i+1;
                        for(int j=1;j<length;j++){
                            if(linebyline[k]==pattern[j]){
                                notsure++;
                                k++;
                            }
                        }
                        if(notsure==length){
                            position[e]=i;
                            e++;
                            dashat++;
                        }
                        notsure=0;
                    }
                }
            } 
        }
        position[e]='\0';
        if(dashat==0 || pos>dashat){
            printf("-1 == No Match Found.\n");
        }
        else{
            printf("The position you were looking for is:%d",position[pos-1]);
        }    
        fclose(myfile);
    }                  
}

void findbyword(char *address,char *pattern){
    int e=0;
    int k=0;
    int notsure=0;
    int dashbyword=0;
    int spacecounter=0;
    int position[1024];
    FILE *myfile;
    char *linebyline=(char *)malloc(1024*sizeof(char));
    pattern=CheckQuote2(pattern);
    int length=strlen(pattern);
    if(pattern[length-1]==' '){
        pattern[length-1]='\0';
    }
    length=strlen(pattern);
    address=CheckQuote2(address);
    myfile=fopen(address,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        while(!feof(myfile)){
            if(fgets(linebyline,1024,myfile)!=NULL){
                for(int i=0;i<strlen(linebyline);i++){
                    if((i!=0) && ((linebyline[i]==' ') || (linebyline[i]=='\0') || (linebyline[i]=='\n'))){
                        spacecounter++;
                    }
                    if(linebyline[i]==pattern[0]){
                        notsure++;
                        k=i+1;
                        for(int j=1;j<length;j++){
                            if(linebyline[k]==pattern[j]){
                                notsure++;
                                k++;
                            }
                        }
                        if(notsure==length){
                            if(e==0){
                                printf("The first word in which the substring was seen is :%d\n",spacecounter+1);
                            }    
                            e++;
                            dashbyword++;
                        }
                        notsure=0;
                    }    
                }    
            }    
        }
        if(dashbyword==0){
            printf("-1 == No Match Found.\n");
        }
        fclose(myfile);
    }        
}

void findall(char *address,char *pattern){
    int e=0;
    int k=0;
    int hint=0;
    int notsure=0;
    int dashbyword=0;
    int spacecounter=0;
    int position[1024];
    FILE *myfile;
    char *linebyline=(char *)malloc(1024*sizeof(char));
    pattern=CheckQuote2(pattern);
    int length=strlen(pattern);
    if(pattern[length-1]==' '){
        pattern[length-1]='\0';
    }
    length=strlen(pattern);
    printf("%d\n",length);
    address=CheckQuote2(address);
    myfile=fopen(address,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        while(!feof(myfile)){
            if(fgets(linebyline,1024,myfile)!=NULL){
                for(int i=0;i<strlen(linebyline);i++){
                    if((i!=0) && ((linebyline[i]==' ') || (linebyline[i]=='\0') || (linebyline[i]=='\n'))){
                        spacecounter++;
                    }
                    if( (linebyline[i]==pattern[0]) ){
                        notsure++;
                        k=i+1;
                        for(int j=1;j<length;j++){
                            if((linebyline[k]==pattern[j])){
                                notsure++;
                                k++;
                            }
                        }
                        if(notsure==length){
                            printf("hi");
                            position[e]=spacecounter+1;
                            e++;
                            dashbyword++;
                        }
                        notsure=0;
                    }    
                }    
            }    
        }
        position[e]='\0';
        if(dashbyword==0){
            printf("-1 == No Match Found.\n");
        }
        else{
            printf("The substring was seen in words with numbers:");    
            for(int u=0;u<e;u++){
                printf("%d",position[u]);
                if(u!=e-1){
                    printf(",");
                }
            }
            printf("\n");
        }
        fclose(myfile);
    }        

}
void find(char *command){
    char *cpy1=(char *)malloc(1024*sizeof(char));
    char *cpy2=(char *)malloc(1024*sizeof(char));
    char *cpy3=(char *)malloc(1024*sizeof(char));
    char *cpy4=(char *)malloc(1024*sizeof(char));
    char *address=(char *)malloc(1024*sizeof(char));
    char *rest=(char *)malloc(1024*sizeof(char));
    strcpy(cpy1,command);
    strcpy(cpy2,command);
    cpy1=CheckQuote4(cpy1);//getting the substring
    cpy2=strstr(cpy2,"--file");//reaching to the --file
    cpy2=strtok(cpy2," ");//separating --file
    cpy2=strtok(NULL,"\n");//separating address of file
    for(int i=0;i<strlen(cpy2);i++){
        //count
        if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"c")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"o")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3],"u")==&cpy2[i+3]) && (strstr(&cpy2[i+4],"n")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"t")==&cpy2[i+5])){
            cpy3[i]='\0';
            strcpy(cpy4,cpy3);
            address=strtok(cpy4,&cpy3[i]);
            rest=strtok(&cpy2[i],"\n");
            findcount(address,cpy1,rest);
            break;            
        }
        //all+byword
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"a")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"l")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3],"l")==&cpy2[i+3]) && (strstr(&cpy2[i+4]," ")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"-")==&cpy2[i+5]) && 
        (strstr(&cpy2[i+6],"b")==&cpy2[i+6]) && (strstr(&cpy2[i+7],"y")==&cpy2[i+7]) && (strstr(&cpy2[i+8],"w")==&cpy2[i+8]) &&
        (strstr(&cpy2[i+9],"o")==&cpy2[i+9]) && (strstr(&cpy2[i+10],"r")==&cpy2[i+10]) && (strstr(&cpy2[i+11],"d")==&cpy2[i+11])){
            cpy3[i]='\0';
        }
        //at+byword
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"a")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"t")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3]," ")==&cpy2[i+3]) && (strstr(&cpy2[i+4],"-")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"b")==&cpy2[i+5]) && 
        (strstr(&cpy2[i+6],"y")==&cpy2[i+6]) && (strstr(&cpy2[i+7],"w")==&cpy2[i+7]) && (strstr(&cpy2[i+8],"o")==&cpy2[i+8]) &&
        (strstr(&cpy2[i+9],"o")==&cpy2[i+9]) && (strstr(&cpy2[i+10],"r")==&cpy2[i+10])){
            cpy3[i]='\0';
        }
        //byword+at
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"b")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"y")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3],"w")==&cpy2[i+3]) && (strstr(&cpy2[i+4],"o")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"r")==&cpy2[i+5]) && 
        (strstr(&cpy2[i+6],"d")==&cpy2[i+6]) && (strstr(&cpy2[i+7]," ")==&cpy2[i+7]) && (strstr(&cpy2[i+8],"-")==&cpy2[i+8]) &&
        (strstr(&cpy2[i+9],"a")==&cpy2[i+9]) && (strstr(&cpy2[i+10],"t")==&cpy2[i+10])){
            cpy3[i]='\0';
        }
        //byword+all
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"b")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"y")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3],"w")==&cpy2[i+3]) && (strstr(&cpy2[i+4],"o")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"r")==&cpy2[i+5]) && 
        (strstr(&cpy2[i+6],"d")==&cpy2[i+6]) && (strstr(&cpy2[i+7]," ")==&cpy2[i+7]) && (strstr(&cpy2[i+8],"-")==&cpy2[i+8]) &&
        (strstr(&cpy2[i+9],"a")==&cpy2[i+9]) && (strstr(&cpy2[i+10],"l")==&cpy2[i+10] && (strstr(&cpy2[i+11],"l")==&cpy2[i+11]))){
            cpy3[i]='\0';
        }
        //byword
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"b")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"y")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3],"w")==&cpy2[i+3]) && (strstr(&cpy2[i+4],"o")==&cpy2[i+4]) && (strstr(&cpy2[i+5],"r")==&cpy2[i+5]) && 
        (strstr(&cpy2[i+6],"d")==&cpy2[i+6]) ){
            cpy3[i]='\0';
            strcpy(cpy4,cpy3);
            address=strtok(cpy4,&cpy3[i]);
            rest=strtok(&cpy2[i],"\n");
            findbyword(address,cpy1);
        }
        //at
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"a")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"t")==&cpy2[i+2])){
            cpy3[i]='\0';
            strcpy(cpy4,cpy3);
            address=strtok(cpy4,&cpy3[i]);
            rest=strtok(&cpy2[i],"\n");
            findat(address,cpy1,rest);
        }
        //all
        else if((strstr(&cpy2[i],"-")==&cpy2[i]) && (strstr(&cpy2[i+1],"a")==&cpy2[i+1]) && (strstr(&cpy2[i+2],"l")==&cpy2[i+2]) &&
        (strstr(&cpy2[i+3],"l")==&cpy2[i+3])){
            cpy3[i]='\0';
            strcpy(cpy4,cpy3);
            address=strtok(cpy4,&cpy3[i]);
            rest=strtok(&cpy2[i],"\n");
            findall(address,cpy1);
        }
        else{
            strcpy(&cpy3[i],&cpy2[i]);
        }
    }
}

void replace(char *command){
    int hint=0;
    int length;
    int length2;
    int length3;
    long long int pos;
    FILE *myfile;
    char *cpy1=(char *)malloc(1024*sizeof(char));
    char *cpy2=(char *)malloc(1024*sizeof(char));//substr1
    char *cpy3=(char *)malloc(1024*sizeof(char));
    char *cpy4=(char *)malloc(1024*sizeof(char));//substr2
    char *cpy5=(char *)malloc(1024*sizeof(char));
    char *cpy6=(char *)malloc(1024*sizeof(char));
    char *cpy7=(char *)malloc(1024*sizeof(char));//address
    char *rest=(char *)malloc(1024*sizeof(char));
    char *wild=(char *)malloc(1024*sizeof(char));
    strcpy(cpy1,command);
    length=strlen(command);
    for(int i=0;i<length;i++){
        if( (strstr(&cpy1[i],"-")==&cpy1[i]) && (strstr(&cpy1[i+1],"-")==&cpy1[i+1]) && (strstr(&cpy1[i+2],"s")==&cpy1[i+2]) && 
        (strstr(&cpy1[i+3],"t")==&cpy1[i+3]) && (strstr(&cpy1[i+4],"r")==&cpy1[i+4]) && (strstr(&cpy1[i+5],"2")==&cpy1[i+5]) ){
            hint=1;
            cpy2[i]='\0';//getting the string we're looking for
            rest=strtok(&cpy1[i],"\n");
            rest=strtok(rest," ");//removing --str2
            rest=strtok(NULL,"\n");
            break;
        }
        else{
            strcpy(&cpy2[i],&cpy1[i]);
        }
    }
    if(hint==1){
        strcpy(cpy3,rest);
        length2=strlen(cpy3);
        for(int x=0;x<length2;x++){
            if( (strstr(&cpy3[x],"-")==&cpy3[x]) && (strstr(&cpy3[x+1],"-")==&cpy3[x+1]) && (strstr(&cpy3[x+2],"f")==&cpy3[x+2]) && 
            (strstr(&cpy3[x+3],"i")==&cpy3[x+3]) && (strstr(&cpy3[x+4],"l")==&cpy3[x+4]) && (strstr(&cpy3[x+5],"e")==&cpy3[x+5]) ){
                cpy4[x]='\0';//getting the new str 
                cpy5=strtok(&cpy3[x],"\n");
                cpy5=strtok(cpy5," ");
                cpy5=strtok(NULL,"\n");
                break;
            }
            else{
                strcpy(&cpy4[x],&cpy3[x]);
            }
        }    
        strcpy(cpy6,cpy5);
        length3=strlen(cpy6);
        for(int z=0;z<length3;z++){
            if( ( (strstr(&cpy6[z],"-")==&cpy6[z]) && (strstr(&cpy6[z+1],"a")==&cpy6[z+1]) && (strstr(&cpy6[z+2],"t")==&cpy6[z+2]) ) || 
            ( (strstr(&cpy6[z],"-")==&cpy6[z]) && (strstr(&cpy6[z+1],"a")==&cpy6[z+1]) && (strstr(&cpy6[z+2],"l")==&cpy6[z+2]) && (strstr(&cpy6[z+3],"l")==&cpy6[z+3]) ) ){
                cpy7[z]='\0';//getting the address
                wild=strtok(&cpy6[z],"\n");
                break;
            }
            else{
                strcpy(&cpy7[z],&cpy6[z]);
            }    
        }
        if( (strstr(&wild[0],"-")==&wild[0]) && (strstr(&wild[1],"a")==&wild[1]) && (strstr(&wild[2],"l")==&wild[2]) && (strstr(&wild[3],"l")==&wild[3]) ){
            //replaceall(cpy2,cpy4,cpy7);
        }
        else{
            wild=strtok(wild," ");
            wild=strtok(NULL,"\n");
            pos=atoll(wild);
        } 
    }

}
void autoindent(char *address){
    int c;
    int left=0;
    int right=0;
    int tabcontrol=0;
    FILE *myfile;
    FILE *tmpfile;
    char rightbraces[1024];
    char leftbraces[1024];
    char *previous=(char *)malloc(2);
    char *cpy1=(char *)malloc(1024*sizeof(char));
    strcpy(cpy1,address);
    cpy1=CheckQuote2(cpy1);
    BackupFile(cpy1);
    myfile=fopen(cpy1,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file.\n");
    }
    else{
        for(int i=0;(c=fgetc(myfile))!=EOF;i++){
            if(c=='{'){
                rightbraces[right]=c;
                right++;
            }
            else if(c=='}'){
                leftbraces[left]=c;
                left++;
            }
        }
        rightbraces[right]='\0';
        leftbraces[left]='\0';
        if(right!=left){
            printf("Oops!The number of right and left braces are not equal.\n");
        }
        else{
            rewind(myfile);
            tmpfile=fopen("/root/tmpfile.txt","w");
            //saving data in a tmp file
            for(int  k=0;(c=fgetc(myfile))!=EOF;k++){
                fputc(c,tmpfile);
            }
            fclose(tmpfile);
            fclose(myfile);
            tmpfile=fopen("/root/tmpfile.txt","r");
            myfile=fopen(cpy1,"w");
            for(int f=0;(c=fgetc(tmpfile))!=EOF;f++){
                if(c=='{'){
                    if((previous[0]!=' ') && (previous[0]!='{') && (previous[0]!='\n')){
                        fputc(' ',myfile);
                    }
                    fputc(c,myfile);
                    fputc('\n',myfile);
                    tabcontrol++;
                    for(int y=0;y<tabcontrol;y++){
                        fputc('\t',myfile);
                    }
                    previous[1]=previous[0];
                    previous[0]='{';
                }
                else if(c=='}'){
                    tabcontrol--;
                    fputc('\n',myfile);
                    for(int r=0;r<tabcontrol;r++){
                        fputc('\t',myfile);
                    }
                    fputc('}',myfile);
                    previous[1]=previous[0];
                    previous[0]='}';
                }    
                if((c!='{') && (c!='}')){
                    fputc(c,myfile);
                    previous[1]=previous[0];
                    previous[0]=c;
                }
            }
            fclose(myfile);
            fclose(tmpfile);
            remove("/root/tmpfile.txt");
            printf("Congrats!The text in you file is marked off by Indentation.\n");
        }
        free(cpy1);
        free(previous);
    }        
}

int QuoteCounter(char *path){
    int QuoteNumerator=0;
    for(int i=0;i<strlen(path);i++){
        if(path[i]=='"'){
            QuoteNumerator++;
        }
    }
    return QuoteNumerator;
}
void TextComparator(char *path){
    int c;
    int j=0;
    int k=0;
    int decider;
    int round=0;
    int round2=0;
    int line1=1;
    int line2=1;
    int help=1;
    FILE *file1;
    FILE *file2;
    bool keep_reading=true;
    char *slash="/";
    char *cpy1=(char *)malloc(1024*sizeof(char));
    char *cpy2=(char *)malloc(1024*sizeof(char));
    char *cpy3=(char *)malloc(1024*sizeof(char));
    char *buffer1=(char *)malloc(1024*sizeof(char));
    char *buffer2=(char *)malloc(1024*sizeof(char));
    strcpy(cpy1,path);
    decider=QuoteCounter(path);
    //finding addresses 
    if(decider==2){//only one of the addresses has Quotation
        for(int i=0;i<strlen(path);i++){
            j=0;
            if(cpy1[i]=='"'){//if the address starts with Quotation mark
                k++;
                cpy2[j]=cpy1[i];
                i++;
                j++;
                while(cpy1[i]!='"'){
                    cpy2[j]=cpy1[i];
                    j++;
                    i++;
                }
                cpy2[j]='\0';
                i++;
                cpy2=CheckQuote2(cpy2);
            }
            else{//if the address doesn't start with Quotation mark
                k++;
                j=0;
                cpy3[j]=cpy1[i];
                i++;
                j++;
                while(cpy1[i]!=' ' || cpy1[i]=='\n'){
                    cpy3[j]=cpy1[i];
                    j++;
                    i++;
                }
                cpy3[j]='\0';                
            }
        }
    } 
    else if(decider==0){//none of the addresses has Quotation
        for(int i=0;i<strlen(path);i++){    
            if(round==0){
                k++;
                j=0;
                cpy2[j]=cpy1[i];
                i++;
                j++;
                while(cpy1[i]!=' ' || cpy1[i]=='\n'){
                    cpy2[j]=cpy1[i];
                    j++;
                    i++;
                }
                cpy2[j]='\0';
                round++;
            }
            if(round==1){
                k++;
                j=0;
                cpy3[j]=cpy1[i];
                i++;
                j++;
                while(cpy1[i]!=' ' || cpy1[i]=='\n'){
                    cpy3[j]=cpy1[i];
                    j++;
                    i++;
                }
                cpy3[j]='\0';
            }
        }
    } 
    else if(decider==4){//both addresses has Quotation
        for(int i=0;i<strlen(path);i++){
            if(round==0){
                j=0;
                if(cpy1[i]=='"'){
                    k++;
                    cpy2[j]=cpy1[i];
                    i++;
                    j++;
                    while(cpy1[i]!='"'){
                        cpy2[j]=cpy1[i];
                        j++;
                        i++;
                    }
                    cpy2[j]='\0';
                    i++;
                    cpy2=CheckQuote2(cpy2);
                    round++;
                }
            }
            if(round==1){
                j=0;
                if(cpy1[i]=='"'){
                    k++;
                    cpy3[j]=cpy1[i];
                    i++;
                    j++;
                    while(cpy1[i]!='"'){
                        cpy3[j]=cpy1[i];
                        j++;
                        i++;
                    }
                    cpy3[j]='\0';
                    i++;
                    cpy3=CheckQuote2(cpy3);
                }    
            }
        } 
    }
    file1=fopen(cpy2,"r");
    file2=fopen(cpy3,"r");
    if((file1==NULL)){
        printf("Oops!Unable to open one of the files.\n");
    }
    else{
        for(int i=0;(c=fgetc(file1))!=EOF;i++){
            if(c=='\n'){
                line1++;
            }    
        }    
        rewind(file2);
        for(int j=0;(c=fgetc(file2))!=EOF;j++){
            if(c=='\n'){
                line2++;
            }    
        }
        rewind(file1);
        rewind(file2);   
        for(int k=1;keep_reading;k++){
            if(line1==line2){
                fgets(buffer1,2048,file1);
                fgets(buffer2,2048,file2);
                help++;
                if(strcmp(buffer1,buffer2)!=0){
                    printf("\n============ #%d ============\n",help);
                    printf("File 1:%s",buffer1);
                    if(help==line1){
                        printf("\n");
                    }
                    printf("File 2:%s",buffer2);
                }
                if((feof(file1)!=0) && (feof(file2)!=0)){
                    keep_reading=false;
                }
            }    
            if(line1>line2){
                fgets(buffer1,2048,file1);
                if(help<=line2){
                    fgets(buffer2,2048,file2);
                    if(strcmp(buffer1,buffer2)!=0 ){
                        printf("\n============ #%d ============\n",help);
                        printf("File 1:%s",buffer1);
                        printf("File 2:%s",buffer2);
                    }
                    if(help==line2){
                        printf("\n");
                    }
                }    
                else{     
                    printf("\n<<<<<<<<<<<< #%d - #%d <<<<<<<<<<<<\n",help,line1);
                    printf("%s",buffer1);
                    if(feof(file1)!=0){
                        keep_reading=false;
                    }
                }    
                help++;
            }
            else if(line2>line1){
                fgets(buffer2,2048,file2);
                if(help<=line1){
                    fgets(buffer1,2048,file1);
                    if(strcmp(buffer1,buffer2)!=0){
                        printf("\n============ #%d ============\n",help);
                        printf("File 1:%s",buffer1);
                        if(help==line1){
                            printf("\n");
                        }
                        printf("File 2:%s",buffer2);
                    }
                }
                else{     
                    printf("\n>>>>>>>>>>>> #%d - #%d >>>>>>>>>>>>\n",help,line2);
                    printf("%s",buffer2);
                    if(feof(file2)!=0){
                        keep_reading=false;
                    }
                }    
                help++;    
            }  
        }    
    }
    fclose(file1);
    fclose(file2);
    free(cpy1);
    free(cpy2);
    free(cpy3);
    free(buffer1);
    free(buffer2);
}

void treeminus1(char *path,const int depth){
    char pathR[1000];
    struct dirent *dp;
    DIR *currentdir=opendir(path);
    if(currentdir==NULL){
        return;
    }
    while((dp=readdir(currentdir))!=NULL){
        if( (strcmp(dp->d_name,".")!=0)  && (strcmp(dp->d_name,"..")!=0) ){
            for(int i=0;i<depth;i++){
                if( (i%2==0) || (i==0) ){
                    printf("%c",179);
                }
                else{
                    printf(" ");
                }
            }
            printf("%c%c%s\n", 195, 196, dp->d_name);
            strcpy(pathR,path);
            strcat(pathR,"/");
            strcat(pathR,dp->d_name);
            treeminus1(pathR,depth+2);
        }
    }
    closedir(currentdir);
}

void tree(char *path,int start,int depth,int controller){
    char pathR[1000];
    struct dirent *dp;
    DIR *currentdir=opendir(path);
    if(currentdir==NULL || controller>depth){
        return;
    }
    while((dp=readdir(currentdir))!=NULL){
        if( (strcmp(dp->d_name,".")!=0)  && (strcmp(dp->d_name,"..")!=0)){
            for(int i=0;i<start;i++){
                if( (i%2==0) && (i==0) ){
                    printf("%c",179);
                }
                else{
                    printf(" ");
                }
            }
            controller++;
            printf("%c%c%s\n", 195, 196, dp->d_name);
            strcpy(pathR,path);
            strcat(pathR,"/");
            strcat(pathR,dp->d_name);
            tree(pathR,start+2,depth,controller);
        }
    }    
    closedir(currentdir);
}

int main(){
    char *path=(char *)malloc(sizeof(char)*10000);
    char *path2=(char *)malloc(sizeof(char)*10000);
    char *command;
    char *command2;
    char *pathR;
    char *pathC;
    int sign;
    int counter=0;
    char *root;
    mkdir("E:/root");
    chdir("E:/root");                      
    while (1){
        gets(path);
        strcpy(path2,path);
        command=strtok(path," ");//recognizing the user's command
        command2=strtok(NULL," ");//recognizing whether it has --file or what
        if( (strcmp(command,"createfile")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the remain of path
            counter=Counting_Directories(pathR);
            makingdirectories(pathR,counter);
        }
        else if( (strcmp(command,"insertstr")==0) && (strcmp(command2,"--file")== 0) ){
            pathR=strtok(NULL,"\n");//getting the remain of path
            insertstr(pathR);
        }
        else if( (strcmp(command,"cat")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the filename & address
            if(strtok(pathR,"\"")!=NULL){
                pathR=strtok(pathR,"\"");
            }
            cat(pathR);
        }
        else if( (strcmp(command,"copystr")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the rest of command
            copy(pathR);
        }
        else if( (strcmp(command,"removestr")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the rest of command
            removestr(pathR);
        }
        else if( (strcmp(command,"cutstr")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the rest of command
            strcpy(pathC,pathR);
            copy(pathR);
            removestr(pathC);
        }       
        else  if( (strcmp(command,"pastestr")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the rest of command
            paste(pathR);
        }
        else if( (strcmp(command,"undo")==0) && (strcmp(command2,"--file")==0) ){
            pathR=strtok(NULL,"\n");//getting the rest of command
            undo(pathR);
        }
        else if( (strcmp(command,"grep")==0) && (strcmp(command2,"--str")==0) ){
            sign=0;
            pathR=strtok(NULL,"\n");//getting the rest of command
            //printf("%s\n",pathR);
            grepempty(pathR,sign);
        }
        else if( (strcmp(command,"grep")==0) && (strcmp(command2,"-C")==0) ){
            sign=1;
            pathR=strtok(NULL," ");
            pathR=strtok(NULL,"\n");//getting the rest of command
            grepempty(pathR,sign);
        }
        else if( (strcmp(command,"grep")==0) && (strcmp(command2,"-I")==0) ){
            sign=2;
            pathR=strtok(NULL," ");
            pathR=strtok(NULL,"\n");//getting the rest of command
            grepempty(pathR,sign);
        }
        else if( (strcmp(command,"find")==0 ) && (strcmp(command2,"--str")==0) ){
            pathR=strtok(NULL,"\n");//getting the rest of command
            find(pathR);
        }
        else if( (strcmp(command,"replace")==0) && (strcmp(command2,"--str1")==0) ){
            pathR=strtok(NULL,"\n");
            replace(pathR);
        }
        else if( (strcmp(command,"auto-indent")==0) ){
            pathR=strtok(path2," ");//separating auto-indent
            pathC=strtok(NULL,"\n");//getting the rest of command
            autoindent(pathC);
        }
        else if( (strcmp(command,"compare")==0) ){
            pathR=strtok(path2," ");
            pathC=strtok(NULL,"\n");
            TextComparator(pathC);
        }
        else if( (strcmp(command,"tree")==0) ){
            int controller=0;
            int rootnum=atoll(command2);
            if(rootnum==-1){
                rootnum=0;
                treeminus1("E:/",rootnum);
            }
            if(rootnum<-1){
                printf("Oops!The depth you entered is invalid.\n");
            }
            else{
                tree("E:/",0,rootnum,controller);
            }
        }
        else if(strcmp(command,"--help")==0){
            printf("Create file:     createfile –file <file name and address>\n");
            printf("Insert:          insertstr –file <file name> –str <str> —pos <line no>:<start position>\n");
            printf("Cat:             cat –file <file name>\n");
            printf("Remove:          removestr –file <file name> –pos <line no>:<start position> -size <number of characters to remove> -f -b <forward or backward>\n");
            printf("Copy:            copystr –file <file name> –pos <line no>:<start position> -size <number of characters to copy> -f -b <forward or backward>\n");
            printf("Cut:             cutstr –file <file name> –pos <line no>:<start position> -size <number of characters to cut> -f -b <forward or backward>\n");
            printf("Paste:           pastestr –file <file name> –pos <line no>:<start position>\n");
            printf("Find:            find –str <str> –file <file name> -wildcard\n");
            printf("Replace:         replace –str1 <str> –str2 <str> –file <file name> [-at <num> | -all]\n");
            printf("Grep:            grep [options] –str <pattern> –files [<file1> <file2> <file3> …]\n");
            printf("Undo:            undo –file <file>\n");
            printf("Closing pairs:   auto-indent <file>\n");
            printf("Tree:            tree <depth>\n");
            printf("Compare:         compare <file1> <file2>\n");
        }
        else{
            printf("invalid command\n");
        }
    }
}