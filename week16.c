#include <stdio.h>
#include<stdlib.h>
#include <string.h>
enum month{January=1,February, March,April, May, June, July, August, September, October, November, December };
typedef struct person{
char name[30];
int date, month, year;//data for date of birth
}person;//define data about that person
int month_30_days(int n)//function to check that if the month has 30 days or not
{
    int month_30days[4]={April,June,September,November};
    int legit=0;
    for(int i=0;i<4;i++)
    {
        if(n==month_30days[i])
            legit=1;
    }
    return legit;
}
int check_leap_year(int n)//function to check leap year
{
    if(n%4==0 && n%100!=0)
        return 1;
    else if(n%4 ==0 && n%100==0 && n%400==0)
        return 1;
    else
        return 0;
}
/*
 * function to check that if the date, month and year of birth user entering is legit or not
 */
int check(const person *ptr)
{

    int legit=1;
    if(ptr->year>=0)
    {
        if(ptr->month>December || ptr->month<January)
            legit=0;
        else
        {
            if(ptr->date<0 || ptr->date>31)
                legit=0;
            else
            {
                /*
                 * check for the legit of date of birth if person was born in 29 February
                 */
                if(ptr->month==February && ptr->date==29 && check_leap_year(ptr->year)==0 )
                    legit=0;
                /*
                 * check for the legit of date of birth if person was born on 31st
                 */
                else if(month_30_days(ptr->month) && ptr->date==31)
                    legit=0;
            }
        }
    }
    else
        legit=0;
    return legit;
}


/*
 * function to check that whether date of birth of previous
 * person is larger than date of birth of current person
 */
int compare(const person *prev_data,const person *cur_data)
{
    if(prev_data->year<cur_data->year)
        return 1;
    else if(prev_data->year==cur_data->year)
    {
        if(prev_data->month>cur_data->month)
            return 0;
        else if(prev_data->month==cur_data->month)
        {
            if(prev_data->date<=cur_data->date)
            {
                return 1;
            }
            else
                return 0;
        }
        else
            return 1;
    }
    else
        return 0;
}
void insertion_sort(person data[],int n)
{
    for(int index=1;index<n;index++)
    {

        int pos=index-1;
        while(compare(&data[pos],&data[index])==1 && pos>=0)
        {
            person temp=data[index];
            data[index]=data[pos];
            data[pos]=temp;

            pos--;
            index--;
        }
    }
}
/*
 * function to take input
 */
void input(person *ptr)
{
    printf("Enter the name: ");
    scanf("%s",ptr->name);
    printf("Enter the date of birth in 'day/month/year' form: ");
    scanf("%d/%d/%d",&(ptr->date),&(ptr->month),&(ptr->year));
    while(check(ptr)==0)
    {
        printf("Please enter the date of birth again:\n");
        scanf("%d/%d/%d",&(ptr->date),&(ptr->month),&(ptr->year));
    }

}
/*
 * function to display the data of person
 */
void print(person *ptr)
{
    printf("Name: %s\n",ptr->name);
    printf("Date of birth (day/month/year): %d/%d/%d\n",ptr->date,ptr->month,ptr->year);
}
void find_people(const person data[],int n,int month_of_birth)
{
    for (int i=0;i<n;i++)
    {
        if(data[i].month==month_of_birth)
            print(&data[i]);
    }
}
int choice(person data[])
{
    printf("MENU \n"
           "1: Enter a person \n"
           "2: Display all birth dates \n "
           "3: Display the youngest person \n"
           "4: Display birthdays in a month \n"
           "0: Quit \n");
    int selection;
    int month_of_birth;
    static int number_of_person=0;
    scanf("%d",&selection);
    switch(selection)
    {
        case 0:
            break;
        case 1:
            input(&data[number_of_person]);
            number_of_person++;
            insertion_sort(data,number_of_person);
            break;
        case 2:
            for(int i=0;i<number_of_person;i++)
                print(&data[i]);
            break;
        case 3:
            printf("The youngest person is: \n");
            print(&data[0]);
            break;
        case 4:
            scanf("%d",&month_of_birth);
              printf("Display all the data of people who has birth day in %d",month_of_birth);
            find_people(data,number_of_person,month_of_birth);
        default:
            printf("Please choose again");
            break;
    }
    return selection;
}
int main() {
    const int MAX_SIZE=100;
    person au[MAX_SIZE];
    int flag=1;
    while(flag!=0)
    {
        flag= choice(au);
    }
    system("pause");//run external console
    return 0;
}
