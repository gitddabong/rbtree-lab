typedef struct human
{
    /* data */
    char name[20];
    int age;
    char gender;

} human;

typedef struct student {
    /* data */
    int s_id;
    char name[20];
    human *man; 
} std;

int main(){
    // struct student st1;
    std st1;
    human hm;
    st1.man = &hm;
    st1.s_id = 10;
    strcpy(st1.man ->name,"Kimseulgi");
    st1.man->age = 25;
    st1.man->gender = 'w';

    printf("s_id  : %d\n", st1.s_id);
    printf("name  : %s\n", st1.man->name);
    printf("age  : %d\n", st1.man->age);
    printf("gender : %c\n", st1.man->gender);
    return 1;

}