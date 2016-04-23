#include <stdio.h>
#include<string.h>
struct tagSTUDENT
{
    int no;
    char name[100];
    int age;
    char qq[100];
    char secret[100];
};
int target=-1;
int size=0;
struct tagSTUDENT users[1000];
struct message
{
    char from[100];
    char to[100];
    char content[1000];

};
struct message messages[10000];
int msg_number=0;
struct blog
{
  char name[100];
  char text[10000];
};
struct blog blogs[100];
int blog_number=0;
void main_panel();
void reg();
void login();
int check_name_valid(char name[100]);
void change_password();
void write_message();
void check_message();
void logout();
void write_blog();
void check_blog();
void load();
void save();

int main()
{
    //TODO: read all users from data.txt
    load();

    int answer;
    printf("If you have an ID? [0/1]:");
    while (1)
    {
        scanf("%d",&answer);
        if (answer == 0)
        {
            reg();
            break;
        }
        else if (answer == 1)
        {
            login();
            break;
        }
        else {
            printf("Please input right command [0/1]:");
        }
    }

    main_panel();

    save();
}

void load()
{
    FILE* f=fopen("data.txt","r");
    if (f != NULL)
    {
        while (fscanf(f,"%s %s %d %d %s\n",users[size].name,
                users[size].secret,&users[size].no,&users[size].age,users[size].qq) != EOF)
        {
            size ++;
        }
        fclose(f);
    }

    FILE* fe=fopen("message.txt","r");
    if(fe!=NULL)
    {
        while (fscanf(fe,"%s%s",messages[msg_number].to,messages[msg_number].from)!=EOF)
        {
            fgets(messages[msg_number].content,100,fe);
            msg_number++;
        }
        fclose(fe);
    }
    FILE* b=fopen("blog.txt","r");
    if(b!=NULL)
    {
        while(fscanf(b,"%s",blogs[blog_number].name)!=EOF)
        {
            fgets(blogs[blog_number].text,10000,b);
            blog_number++;
        }
        fclose(b);
    }

}

void save()
{
    FILE* fw=fopen("data.txt","w");
    for (int i = 0; i < size; i++)
    {
        fprintf(fw,"%s %s %d %d %s \n",users[i].name,
                users[i].secret,users[i].no,users[i].age,users[i].qq);
    }
    fclose(fw);
    FILE* fe=fopen("message.txt","w");
    for(int i=0; i<msg_number; i++)
        fprintf(fe,"%s %s %s\n",messages[i].to,messages[i].from,messages[i].content);
    fclose(fe);
    FILE* b=fopen("blog.txt","w");
    for(int i=0; i<blog_number;i++)
        fprintf(b,"%s %s\n",blogs[i].name,blogs[i].text);
    fclose(b);

}

void main_panel()
{

    int number;
    while(number!=8){
        printf("Please choose your command:\n");
        printf("1 Change the password\n");
        printf("2 Change your profile\n");
        printf("3 Search the member\n");
        printf("4 send massage to others\n");
        printf("5 search the massage from others\n");
        printf("6 write blogs\n");
        printf("7 look for others blogs\n");
        printf("8 exit\n");
        scanf("%d",&number);
        switch(number)
        {
        case 1:
            change_password();
            break;
        case 2:
            change_profile();
            break;
        case 3:
            search_member();
            break;
        case 4:
            write_message();
            break;
        case 5:
            check_message();
            break;
        case 6:
            write_blog();
            break;
        case 7:
            check_blog();
            break;
        case 8:
            printf("Logout\n");
            break;
        }
    }
}

int check_name_valid(char name[100])
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(name, users[i].name) == 0)
            return 1;
    }
    return 0;
}

void reg()
{
    struct tagSTUDENT x;
    printf("Please creat your ID:");
    scanf("%s",x.name);

    while (check_name_valid(x.name))
    {
        printf("The name has been used, please renter your name:");
        scanf("%s", x.name);
    }

    printf("Please enter your password:");
    scanf("%s",x.secret);
    printf("Please enter your Student Number:");
    scanf("%d",&x.no);
    printf("Please enter your age:");
    scanf("%d",&x.age);
    printf("Please enter your qq Number:");
    scanf("%s",x.qq);

    users[size++] = x; //
}

void login()
{
    while(target<0)
    {
        struct tagSTUDENT x;
        printf("Please enter your ID:\n");
        scanf("%s",x.name);
        printf("Please enter your Password\n");
        scanf("%s",x.secret);

        for(int i=0; i<size; i++)
        {
            if((strcmp(x.secret,users[i].secret)==0)&&(strcmp(x.name,users[i].name)==0))
            {
                target=i;
                printf("login successfully!\n");
                break;
            }

        }
        if(target<0)
            printf("Your massage is wrong!");
    }

}

void change_password()
{
    struct tagSTUDENT x;
    printf("Please enter your new password:");
    scanf("%s",x.secret);
    strcpy(users[target].secret,x.secret);
    printf("Change successfully\n");

}

void change_profile()
{
    struct tagSTUDENT x;
    printf("Please choose your item:");
    printf("1 Change your no:");
    printf("2 Change your qq:");
    printf("3 Change your age:");
    int number;
    scanf("%d",&number);
    switch (number)
    {
    case 1:
        printf("Please enter your new no:");
        scanf("%d",&x.no);
        users[target].no=x.no;
        break;
    case 2:
        printf("Please enter your qq:");
        scanf("%s",x.qq);
        strcpy(users[target].qq,x.qq);
        break;
    case 3:
        printf("Please enter your age:");
        scanf("%d",&x.age);
        users[target].age=x.age;
        break;
    }
    printf("Change successfully!\n");
}
void search_member()
{
    int check=0;
    while(check==0)
    {
        struct tagSTUDENT x;
        printf("Please enter the ID:");
        scanf("%s",x.name);
        for(int i=0; i<size; i++)
        {
            if(strcmp(x.name,users[i].name)==0)
            {
                printf("name:%s\nqq:%s\nage:%d\nno:%d\n",users[i].name,users[i].qq,&users[i].age,&users[i].no);
                check=1;
                break;
            }

        }
    }
}
void write_message()
{
    struct message s;
    int correct=0;
    while(correct==0)
    {

        printf("Please enter your friend's ID:");
        scanf("%s",s.to);
        strcpy(s.from,users[target].name);
        printf("Please write your message:");
        getchar();
        gets(s.content);
        printf("Weather your want to send this message?");
        int answer;
        scanf("%d",&answer);
        if(answer==1)
        {
            messages[msg_number++]=s;
            printf("your message has been sent successfully!\n");
            correct=1;
        }
    }
}
void check_message()
{
    struct message s;
    int count=0;
    for(int i=msg_number; i>=0; i--)
    {
        if(strcmp(messages[i].to,users[target].name)==0)
        {
            count++;
            printf("Message %d From: %s Content: %s",count,messages[i].from,messages[i].content);
        }
    }
}

void write_blog()
{
    struct blog t;
    printf("Please write your blog:");
    getchar();
    gets(t.text);
    strcpy(t.name,users[target].name);
    blogs[blog_number++]=t;
    printf("Your blog has been reserved successfully!\n");

}
void check_blog()
{
    char name[100];
    printf("Please enter the name you want to search:");
    scanf("%s",name);
    for(int i=0; i<blog_number; i++)
    {
    if(strcmp(blogs[i].name,name)==0)
       printf("%s\n",blogs[i].text);
    }
}




