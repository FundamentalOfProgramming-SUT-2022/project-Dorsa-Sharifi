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

//Main Functions
void Createfile(char *);
void insertstr(char *);
void cat(char *);
void copy(char *);
void removestr(char *);
void paste(char *);
void undo(char *);
void grepempty(char *,int );

//Auxiliary Functions
char *CheckQuote(char *);
char *CheckQuote2(char *);
char *CheckQuote3(char *command);
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
    myfile=fopen(address,"r");
    if(myfile==NULL){
        printf("Oops!Unable to open the file!.\n");
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

int main(){
    char *path=(char *)malloc(sizeof(char)*10000);
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
    }
}