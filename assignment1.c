#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


pthread_t tid[2];
int counter;

typedef struct student {
   char  name[50];
   float GPA;
   unsigned int Toeic_score;
   unsigned int obtained_credits;
   unsigned int tuition;
} Student;

// Critical section
Student *dtrgiang = &(Student) {
    "Do Truong Giang",
    2.5,
    100,
    85,
    10000000
};

pthread_mutex_t lock;

void *update_student_infor(Student *student_information)
{

    char email_mess[250];
    char temp_mess[100];

    pthread_mutex_lock(&lock);
    counter += 1;

    strcpy(email_mess, "Subject: Cap nhat thong tin sinh vien\n");

    sprintf(temp_mess, "Thong tin cua ban da bi thay doi boi thread %d.\n", counter);
    strcat(email_mess, temp_mess);

    printf("Thread %d.\n", counter);
    printf("Thong tin sinh vien truoc khi chinh sua:\n");
    printf("Ho ten: %s, GPA: %.2f, Toeic: %d, So tin chi dat duoc: %d, Hoc phi no: %d.\n", dtrgiang->name, dtrgiang->GPA, dtrgiang->Toeic_score, dtrgiang->obtained_credits, dtrgiang->tuition);

    if(strcmp(dtrgiang->name, student_information->name)){
        sprintf(temp_mess, "Ten ban duoc cap nhat thanh %s.\n", student_information->name);
        strcat(email_mess, temp_mess);
    }
    if(dtrgiang->GPA != student_information->GPA){
        sprintf(temp_mess, "GPA duoc cap nhat thanh %.1f.\n", student_information->GPA);
        strcat(email_mess, temp_mess);
    }
    if(dtrgiang->Toeic_score != student_information->Toeic_score){
        sprintf(temp_mess, "Diem Toeic duoc cap nhat thanh %d.\n", student_information->Toeic_score);
        strcat(email_mess, temp_mess);
    }
    if(dtrgiang->obtained_credits != student_information->obtained_credits){
        sprintf(temp_mess, "So tin chi duoc cap nhat thanh %d.\n", student_information->obtained_credits);
        strcat(email_mess, temp_mess);
    }
    if(dtrgiang->tuition != student_information->tuition){
        sprintf(temp_mess, "No hoc phi duoc cap nhat thanh %d.\n", student_information->tuition);
        strcat(email_mess, temp_mess);
    }

    dtrgiang = student_information;
    printf("Thong tin sinh vien sau khi chinh sua:\n");
    printf("Ho ten: %s, GPA: %.2f, Toeic: %d, So tin chi dat duoc: %d, Hoc phi no: %d.\n", dtrgiang->name, dtrgiang->GPA, dtrgiang->Toeic_score, dtrgiang->obtained_credits, dtrgiang->tuition);
    printf("\n");

    pthread_mutex_unlock(&lock);

    sleep(1);

    char cmd[100];
    // char recipient[] = "dtr.giang.1299@gmail.com";
    char recipient[] = "giang.dt172524@sis.hust.edu.vn";
    char tempMailFile[50];

    strcpy(tempMailFile, tempnam("/tmp", "sendmail"));

    FILE *fp = fopen(tempMailFile, "w");
    fprintf(fp, "%s\n", email_mess);
    fclose(fp);

    // sprintf(cmd, "sendmail %s < %s", recipient, tempMailFile);
    system(cmd);
}

int main()
{
    int i = 0;
    int err;

    Student dtrgiangs[2] = {*dtrgiang, *dtrgiang};
    dtrgiangs[0].GPA =  3.0;
    dtrgiangs[0].Toeic_score = 450;
    dtrgiangs[0].tuition = 200000000;

    dtrgiangs[1].GPA =  3.5;
    dtrgiangs[0].Toeic_score = 500;
    dtrgiangs[1].tuition = 3000000;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &update_student_infor, (Student *)&dtrgiangs[i]);
        if (err != 0)
            printf("\nFail creating thread :[%s]", strerror(err));
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

    printf("\nSau khi hai thread hoan thanh:\n");
    printf("Ho ten: %s, GPA: %.2f, Toeic: %d, So tin chi dat duoc: %d, Hoc phi no: %d.\n", dtrgiang->name, dtrgiang->GPA, dtrgiang->Toeic_score, dtrgiang->obtained_credits, dtrgiang->tuition);

    return 0;
}