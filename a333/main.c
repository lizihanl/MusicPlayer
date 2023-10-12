
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define MAX_LINES 1000
//最大行数
//#define NUMBERS_PER_PAGE 5
//每页显示的产品数量
#define N 100
//单行最大读取数

struct laptop{
    char brand[20];
    float price;
};


int getPriceData(FILE *fpWork,struct laptop *arrLaptop)
{
    char str[N+1];
    int count=0;                   //产品数
//    char flag=0;
//    int readflag=1;                 //1:brand,0:price
    int i=0;
    int j=0;
    int k=0;

//    char brand[50];
//    float price;
    char chPrice[20];

    while((fgets(str,N,fpWork))!=NULL)
    {

//        printf("linestr:%s\n", str);
        while((str[i]!=9)&&((str[i]!=' ')||((str[i]==' ')&&(str[i+1]!=' '))))
        {
            arrLaptop[k].brand[i]=str[i];
            i++;
        }
        arrLaptop[k].brand[i]='\0';
        i++;
        while((str[i]==9)||(str[i]==' '))
        {
            i++;
        }
        while(str[i]!='\0')
        {
            chPrice[j]=str[i];
            i++;
            j++;
        }
        chPrice[j]='\0';
        arrLaptop[k].price=(float )atof(chPrice);
//            printf("ch:  %c s: %s\n",chPrice[0],chPrice);
//            printf("pp:  %f  \n",price);
        count++;
        i=0;
        j=0;
//        printf("品牌：%-10s   价格:%g\n",arrLaptop[k].brand,arrLaptop[k].price);
        k++;
    }

//    printf("n=%d\n",count);
    return count;
}


void displayList(struct laptop *arrLaptop,int count,int numberPerPage)
{
    int i=0;
    int j;
    int k;
    int pages=(int)((count+numberPerPage-1)/numberPerPage);
//    printf("no.=%d\n",numberPerPage);
    int cc;
    for(k=0;(k<pages&&cc!='q');k++)              //&&c!='q'
    {
        for(j=0;(j<numberPerPage&&i<count);j++)
        {
            printf("%-10s%g\n",arrLaptop[i].brand,arrLaptop[i].price);
//            printf("i= %d  p=%d\n",i,pages);
            i++;
        }
        if (i!=count)
        {
            printf("press 'space' key to next page and press 'q' key exit.\n");
            do
            {
//                scanf("%c",&c);
                cc=getchar();
            }while((cc!='q')&&(cc!=' '));
        }
    }
}
void priceSort(struct laptop *arrLaptop,int count)
{
    int i,j;
    float temp;
    char temp_ch[20];
    for(i=0;i<count-1;i++)
    {
        for(j=0;j<count-1-i;j++)
        {
            if(arrLaptop[j].price>arrLaptop[j+1].price)
            {
                temp = arrLaptop[j].price;
                arrLaptop[j].price=arrLaptop[j+1].price;
                arrLaptop[j+1].price=temp;

                strcpy(temp_ch,arrLaptop[j].brand);
                strcpy(arrLaptop[j].brand,arrLaptop[j+1].brand);
                strcpy(arrLaptop[j+1].brand,temp_ch);
            }
        }
    }
}

int main(int argc,char *argv[])
//{
//int main()
{
//    int argc;
//    char *argv[];
//    int c;
    FILE  *fp;
    int numberOfProduct;
//    struct laptop arr_laptop[MAX_LINES];
    struct laptop *arr_laptop = malloc(MAX_LINES * sizeof *arr_laptop);
    if (arr_laptop == NULL) {
        printf(" No memory is allocated.");
        exit(0);
    }

    if (argc!=3){
        printf("number of arguments is wrong!\n");
        exit(-1);
    }
//    while (flag!=0)
//    {
    if ((fp = fopen(argv[1], "r")) == NULL)             //argv[1]    "../input.txt"
    {
        printf("file %s can't opened\n",argv[1]);
//            printf("can't open\n");
        exit(-1);
    }

    numberOfProduct = getPriceData(fp,arr_laptop);
//        printf("flag:%d\n",flag);
    priceSort(arr_laptop,numberOfProduct);
    displayList(arr_laptop, numberOfProduct, atoi(argv[2]));
    fclose(fp);
//    }
    free(arr_laptop);




//    printf("Process finished with exit code 0\n");
    return 0;
}

