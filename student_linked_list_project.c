#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

typedef struct student
{
        int rollno;
        char name[20];
        float marks;
        struct student*next;

}sll;

void addbegin(sll**);
void printnode(sll*);
int countnode(sll*);
void savefile(sll*);
void deleteall(sll**);
void addend(sll**);
void readfile(sll**);
void addmiddle(sll**);
void reverseprint(sll*);
void printrec(sll*);
void reversearch(sll*);
void searchnode(sll*);
void sortdata(sll*);
void deletenode(sll**);
void reverselinks(sll**);

int main()
{
        sll*head=0;
        int c,op;

        while(1)
        {
                printf("\033[32menter your choice\n\033[0m");
                printf("1] addbegin\n"
                       "2] addend\n"
                       "3] addmiddle\n"
                       "4] printnode\n"
                       "5] count node\n"
                       "6] savefile\n"
                       "7] readfile\n"
                       "8] reverseprint\n"
                       "9] printrec\n"
                       "10] reverserec\n"
                       "11] deleteall\n"
                       "12] deletenode\n"
                       "13] searchnode\n"
                       "14] sortdata\n"
                       "15] reverselinks\n"
                       "16] EXIT\n");

                scanf("%d",&op);

                switch(op)
                {
                        case 1: addbegin(&head); break;
                        case 2: addend(&head); break;
                        case 3: addmiddle(&head); break;
                        case 4: printnode(head); break;
                        case 5:
                                c=countnode(head);
                                printf("total count=%d\n",c);
                                break;
                        case 6: savefile(head); break;
                        case 7: readfile(&head); break;
                        case 8: reverseprint(head); break;
                        case 9: printrec(head); break;
                        case 10: reversearch(head); break;
                        case 11: deleteall(&head); break;
                        case 12: deletenode(&head); break;
                        case 13: searchnode(head); break;
                        case 14: sortdata(head); break;
                        case 15: reverselinks(&head); break;
                        case 16: exit(0);
                        default:
                                printf("\033[31;1;4;5munknown choice\033[0m\n");
                }
        }
}

void addbegin(sll**ptr)
{
        sll*new;
        new=malloc(sizeof(sll));

        printf("enter rollno,name,marks\n");
        scanf("%d %s %f",&new->rollno,new->name,&new->marks);

        new->next=*ptr;
        *ptr=new;
}

void printnode(sll*ptr)
{
        printf("\033[34m***********\n");

        if(ptr==0)
        {
                printf("no record found\n");
                printf("************************\033[0m\n");
                return;
        }

        while(ptr)
        {
                printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                ptr=ptr->next;
        }

        printf("\033[0m");
}

int countnode(sll*ptr)
{
        int c=0;

        while(ptr)
        {
                c++;
                ptr=ptr->next;
        }

        return c;
}

void savefile(sll*ptr)
{
        if(ptr==0)
        {
                printf("no records found\n");
                printf("****************\n");
                return;
        }

        FILE*fp=fopen("std.txt","w");

        if(fp==0)
        {
                printf("file opening error\n");
                return;
        }

        while(ptr)
        {
                fprintf(fp,"%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                ptr=ptr->next;
        }

        printf("data save in file successfully\n");
        printf("********************\033[0m\n");

        fclose(fp);
}

void deleteall(sll**ptr)
{
        if(*ptr==0)
        {
                printf("no record found\n");
                return;
        }

        int c=1;
        sll*del=*ptr;

        while(del)
        {
                *ptr=del->next;
                printf("node deleted:%d\n",c++);
                sleep(1);
                free(del);
                del=*ptr;
        }

        printf("all nodes are deleted\n");
}

void addend(sll**ptr)
{
        sll*new,*last;

        new=malloc(sizeof(sll));

        printf("enter roll name and marks\n");
        scanf("%d %s %f",&new->rollno,new->name,&new->marks);

        new->next=0;

        if(*ptr==0)
                *ptr=new;
        else
        {
                last=*ptr;
                while(last->next)
                        last=last->next;
                last->next=new;
        }
}

void readfile(sll**ptr)
{
        sll*new,*last;
        FILE*fp;

        fp=fopen("std.txt","r");

        if(fp==0)
        {
                printf("student database not present\n");
                return;
        }

        while(1)
        {
                new=malloc(sizeof(sll));

                if(fscanf(fp,"%d %s %f",&new->rollno,new->name,&new->marks)!=3)
                {
                        free(new);
                        break;
                }

                new->next=0;

                if(*ptr==0)
                        *ptr=new;
                else
                {
                        last=*ptr;
                        while(last->next)
                                last=last->next;
                        last->next=new;
                }
        }

        fclose(fp);
}

void addmiddle(sll**ptr)
{
        sll*new,*pos;

        new=malloc(sizeof(sll));

        printf("enter the rollno name and marks\n");
        scanf("%d %s %f",&new->rollno,new->name,&new->marks);

        if((*ptr==0)||(new->rollno<(*ptr)->rollno))
        {
                new->next=*ptr;
                *ptr=new;
        }
        else
        {
                pos=*ptr;

                while(pos->next!=0 && (new->rollno>pos->next->rollno))
                        pos=pos->next;

                new->next=pos->next;
                pos->next=new;
        }
}

void reverseprint(sll*ptr)
{
        if(ptr==0)
        {
                printf("no record found\n");
                return;
        }

        int c=countnode(ptr);
        int i,j;
        sll*t;

        for(i=0;i<c;i++)
        {
                t=ptr;

                for(j=0;j<c-1-i;j++)
                        t=t->next;

                printf("%d %s %f\n",t->rollno,t->name,t->marks);
        }
}

void printrec(sll*ptr)
{
        if(ptr)
        {
                printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);

                if(ptr->next!=0)
                        printrec(ptr->next);
        }
        else
                printf("no records found\n");
}

void reversearch(sll*ptr)
{
        if(ptr)
        {
                reversearch(ptr->next);
                printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
        }
        else
                printf("no record found\n");
}

void searchnode(sll*ptr)
{
        if(ptr==0)
        {
                printf("no records found\n");
                return;
        }

        int f=0;
        char name[20];

        printf("enter the name to search\n");
        scanf("%s",name);

        while(ptr)
        {
                if(strcmp(name,ptr->name)==0)
                {
                        f=1;
                        printf("%d %s %f\n",ptr->rollno,ptr->name,ptr->marks);
                }

                ptr=ptr->next;
        }

        if(f==0)
                printf("%s:not found\n",name);
}

void sortdata(sll*ptr)
{
        if(ptr==0)
        {
                printf("no records found\n");
                return;
        }

        sll*p1,*p2,t;
        int i,j,c=countnode(ptr);

        for(i=0;i<c-1;i++)
        {
                p1=ptr;
                p2=ptr->next;

                for(j=0;j<c-1-i;j++)
                {
                        if(p1->rollno>p2->rollno)
                        {
                                t.rollno=p1->rollno;
                                strcpy(t.name,p1->name);
                                t.marks=p1->marks;

                                p1->rollno=p2->rollno;
                                strcpy(p1->name,p2->name);
                                p1->marks=p2->marks;

                                p2->rollno=t.rollno;
                                strcpy(p2->name,t.name);
                                p2->marks=t.marks;
                        }

                        p1=p1->next;
                        p2=p2->next;
                }
        }
}

void deletenode(sll**ptr)
{
        if(*ptr==0)
        {
                printf("no record found\n");
                return;
        }

        char name[20];

        printf("enter the name to delete\n");
        scanf("%s",name);

        sll*del=*ptr,*prev=0;

        while(del)
        {
                if(strcmp(name,del->name)==0)
                {
                        if(del==*ptr)
                                *ptr=del->next;
                        else
                                prev->next=del->next;

                        free(del);
                        return;
                }

                prev=del;
                del=del->next;
        }

        printf("name not found\n");
}

void reverselinks(sll**ptr)
{
        if(*ptr==0)
        {
                printf("no record found\n");
                return;
        }

        int i,c=countnode(*ptr);
        sll**a;
        sll*t=*ptr;

        if(c>1)
        {
                a=malloc(sizeof(sll*)*c);

                for(i=0;i<c;i++)
                {
                        a[i]=t;
                        t=t->next;
                }

                for(i=c-1;i>0;i--)
                        a[i]->next=a[i-1];

                a[0]->next=0;
                *ptr=a[c-1];

                free(a);
        }
}
