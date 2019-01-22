//
//  main.c
//  Hangman2
//
//  Created by Supapat on 15/1/2562 BE.
//  Copyright © 2562 Supapat. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <struct.h>
void String_Lower(char string[])
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] >= 'A' && string[i] <= 'Z') {
            string[i] = string[i] + 32;
        }
        i++;
    }
}
//ฟังก์ชั่นโหลดไฟล์ งาน
void Load_File (char filename[],char word[][20],char hint[][20], int *stcount) {
    //กำหนดชื่อไฟล์เป็น fp
    FILE *fp;
    char wordq[20],hintq[20];
    char ch[1];
    char first[20];
    // ในขณะที่เปิดไฟล์ได้้
    if ((fp = fopen(filename, "r")) != NULL ){
        *stcount=0;
        // scan ข้อมูล ตามแบบ
        fscanf(fp,"%s",first);
        fgetc(fp);
        while (fscanf(fp,"%[^,],%[^,],%c",wordq,hintq,ch)==3)
        {
            strcpy(word[*stcount],wordq);
            strcpy(hint[*stcount],hintq);
            *stcount = *stcount+1;
        }
        fclose(fp);
        //printf("\nTotal read %d records.\n",*stcount);
        
    }
    else
        printf("\nError Can't Read File\n");
}
void createunder (char underscore[],unsigned long count)
{
    int i=0;
    for (i=0; i<count; i++) {
        underscore = strcat(underscore, "_");
    }
    printf("%s\n",underscore);
}
int is_match(char word[],char input[],char under[])
{
    int i=0;
    int found = 0;
    unsigned long count = strlen(word);
    for(i=0;i<=count;i++)
    {
        if(word[i]==input[0])
        {
            under[i] = input[0];
            found++;
        }
    }
    return found;
}
int is_unsame(char under[],char input[])
{
    int i=0;
    for(i=0;i<=strlen(under);i++)
    {
        if(under[i]==input[0])
        {
            return 0;
        }
    }
    return 1;
}
int main(int argc, char **argv) {
    char word[10][20];
    char hint[10][20];
    char wrong[20];
    int count = 0;
    char underscore[20];
    char input[]="";
    int found=0;
    char filename[20];
    unsigned long remain;
    int choice;
    unsigned long guess = 0;
    char newgame = '\0';
    int score = 100;
    
    //Start----
    printf("Welcome to Hangman!\n");
    printf("1.Sport Around the world\n");
    printf("2.Soft Drink\n");
    do {
    do {
        //catergory
        printf("Before start please choose your favourite category(1/2) \n=>");
        rewind(stdin);
        scanf("%d",&choice);
        if (choice==1) {
            strcpy(filename,"word1.txt");
        }
        else if(choice==2){
            strcpy(filename,"word2.txt");
        }
    } while (isalpha(choice)||choice>2||choice<=0);
        srand(time(NULL));
    Load_File(filename,word,hint, &count);
        if(count!=0){
            int r = rand() % count;
            printf("Hint => %s\n",hint[r]);
            createunder(underscore, strlen(word[r]));
            remain = strlen(word[r]);
            guess = strlen(word[r]);
            while (remain!=0&&guess!=0) {
                printf(">");
                gets(input);
                String_Lower(input);
                if(is_unsame(underscore, input)){
                    remain=remain-is_match(word[r],input,underscore);
                    if (is_match(word[r],input,underscore)==0) { //Not Found!
                        for(int k=0;k<=strlen(wrong);k++){
                            if(wrong[k]==input[0])
                                found=1;
                        }
                        if (found==0) {
                            strcat(wrong, input);
                            strcat(wrong, " ");
                            score = score - (100/strlen(word[r]));
                            guess--;
                        }
                        else{
                            printf("Enter same!\n");
                            found=0;
                        }
                    }
                    printf("\n%s Score %d,remaing wrong guess:%lu wrong guess:%s\n",underscore,score,guess,wrong);
                }
            }
            if(remain==0){
                printf("You Got it!\n");
            }
            else
                printf("You Failed try again!\n");
            rewind(stdin);
            memset(underscore, 0, sizeof underscore);
            printf("Do you want to try again? (y) exit(any)");
            scanf("%s",&newgame);
        }
        
    } while (newgame=='y'||newgame=='Y');
}
