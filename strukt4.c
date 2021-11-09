#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

typedef struct Data{
    int koef;
    int exp;
    struct Data* next;
}data;

int InsertAfter(data* first, data* second);
data* FindLast(data* head);
int FreeList(data* head);
int PrintListMult(data* head);
int PrintListAdd(data* head);
data* FindMemberBefore(data* inputMember, data* head);
int SortOnInsert(data* newData, data* head);
long Multiplication(data* head);
long Addition(data* head);

int main()
{
    FILE* fp=NULL;
    char line[1024]={0};
    char fileName[40]={0};
    char sign[2]={0};
    int cursor=0, space=0;
    int checkSscan=0;
    long num=0;
    data head={.koef=0, .exp=0, .next=NULL};
    data* newData=NULL;

    printf("Input file name:\t");
    scanf(" %s", fileName);

    fp=fopen(fileName, "r");
    if(fp==NULL){
        printf("ERROR\n");
        return -1;
    }

    fseek(fp, 0, SEEK_SET);

    //UNOS
    while(fgets(line, sizeof(line), fp)!=NULL){

            newData=(data*)malloc(sizeof(data));
            if(newData==NULL){
                return -1;
            }

            checkSscan=sscanf(line, " %d %d %n", &newData->koef, &newData->exp, &space);

            if(checkSscan==EOF){
                continue;
            }
            else if(checkSscan!=2){
                printf("Given file is not formatted correctly\n");
                return -1;
            }
            else{
                    cursor+=space;
                    if(newData->koef==0){
                        free(newData);
                    }
                    else{
                            SortOnInsert(newData, &head);
                        }
                    rewind(fp);
                    fseek(fp, cursor, SEEK_SET);
                }
    }

    while(1){
        printf("\n-----------------------------------------------------------------"
               "\nTo multiplicate:\t*"
               "\nTo add:\t\t\t+"
               "\n-----------------------------------------------------------------\n");
        printf("User input:\t");
        scanf(" %s", sign);

        if(strcmp(sign, "*")==0){
            PrintListMult(&head);
            num=Multiplication(&head);
            break;
        }
        else if(strcmp(sign, "+")==0){
            PrintListAdd(&head);
            num=Addition(&head);
            break;
        }
        else{
            printf("\nWrong input...Try again!");
        }
    }
    if(num==-1){
            return -1;
        }
    printf("\nResult:\t%ld\n", num);
    if(FreeList(&head)==0){
        return 0;
    }

}

long Multiplication(data* head)
{
    int scan=0;
    long mult=0;
    int tempKoef=1;
    int tempExp=0;
    data* temp=head->next;
    data* pom=temp->next;

    printf("\nInput x (whole number):\t");
    if(scanf(" %d", &scan)!=1){
        printf("\nInput ERROR!\n");
        return -1;
    }
    if(temp==NULL){
        return 0;
    }
    while(temp){
            tempKoef = tempKoef * (temp->koef);
            tempExp += (temp->exp);
            temp=temp->next;
    }

    mult=(long)tempKoef*((pow(scan, tempExp)+0.5));

    return mult;
}

long Addition(data* head)
{
    int scan=0;
    long add=0;
    data* temp=head->next;

    printf("\nInput x (whole number):\t");
    scanf(" %d", &scan);

    if(temp==NULL){
        return 0;
    }

    while(1){
        add += (temp->koef)*((long)(pow(scan, temp->exp) + 0.5));
        if(temp->next){
            temp=temp->next;
        }
        else
            break;
    }
    return add;
}


int SortOnInsert(data* newData, data* head)
{
        int koefic=0;
        data* temp=head->next;
        data* tempHead=head;
        data* before=NULL;

        if(tempHead->next==NULL){
            InsertAfter(tempHead, newData);
            return 0;
        }
        else if((newData->exp) > (tempHead->next->exp)){
            InsertAfter(tempHead, newData);
            return 0;
        }
        else if((newData->exp) == (tempHead->next->exp)){
            koefic= tempHead->next->koef + newData->koef;
            tempHead->next->koef =koefic;
            free(newData);
            return 0;
        }
        else {
            while(1){
                koefic=0;

                if((temp->next==NULL) && (newData->exp > temp->exp)){
                            before=FindMemberBefore(temp, head);
                            InsertAfter(before, newData);
                            return 0;
                        }
                else if((temp->next==NULL) && (newData->exp == temp->exp)){
                            koefic= temp->koef + newData->koef;
                            temp->koef = koefic;
                            free(newData);
                            return 0;
                        }
                else if((temp->next==NULL) && (newData->exp < temp->exp)){
                            InsertAfter(temp, newData);
                            return 0;
                        }
                else if((temp->exp > newData->exp) && (newData->exp > temp->next->exp)){
                            InsertAfter(temp, newData);
                            return 0;
                        }
                else{
                   temp=temp->next;
                   continue;
                }
            }
        }
}

data* FindMemberBefore(data* temp, data* head) //Finding the one before(before starts from the head and looks for a member before the inputMember)
{
    data* before=head;

    while(before->next!=temp){
        before=before->next;
    }
    printf("\nKoef:\t%d"
           "\neksp:\t%d", before->koef, before->exp);
    return before;
}

int FreeList(data* head)
{
    data* temp=NULL;
    head=head->next;
    while (head)
    {
       temp = head;
       head=head->next;
       free(temp);
    }
    printf("\n(Successfully freed!)\n");
    return 0;
}

int PrintListMult(data* head)
{

    int br=0;
    data* temp=head->next;

    if(temp==NULL){
        printf("\nList is empty!\n");
        return -1;
    }
    printf("\n");
    while(1){
        printf("%dx^%d", temp->koef, temp->exp);
        if(temp->next){
            printf(" * ");
            temp=temp->next;
        }
        else{
            printf("\n");
            break;
        }
    }
    printf("\n");
    return 0;
}

int PrintListAdd(data* head)
{

    int br=0;
    data* temp=head->next;

    if(temp==NULL){
        printf("\nList is empty!\n");
        return -1;
    }
    printf("\n");
    while(1){
        printf("%dx^%d", temp->koef, temp->exp);
        if(temp->next){
            printf(" + ");
            temp=temp->next;
        }
        else{
            printf("\n");
            break;
        }
    }
    return 0;
}
data* FindLast(data* head)
{
    data* temp=head;
    while(temp->next){
        temp=temp->next;
    }
    return temp;
}

int InsertAfter(data* first, data* second)
{
    second->next=first->next;
    first->next=second;
    return 0;
}
