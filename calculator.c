#include <stdio.h>
//输入/*才是乘法
//合法数字的检验:负号仅能出现在第一位或e后
//小数点仅能出现在两数字中间,e前面,且只能出现一次
//e仅能出现在一位数字后,且e后也应为合法数字(仅能为负号+数字 或者 纯数字),且仅出现一次
//00.10不合法
//检查3个输入 数字 符号 数字
//符号:+-*/
//数字:格式合法 纯数字,科学计数法(x.xexxx),小数(xxx.xxx),负号(-xxx)

int num1[100000+5],sci1,lenth1;
int num2[100000+5],sci2,lenth2;
int ans[200000+5],asci,alenth;
//num[0]:为符号,sci:科学计数法的数字,lenth:num长度

int notnum(char *p);//检查是否为合法数字,不合法返回1
int valid(int num,char **p);//检查输入是否合法
void output();//输出
void getnum(int*num,int *osci,int *olenth,char *p);//把字符数组转换为数字数组
void add(int num1[],int sci1,int lenth1,int num2[],int sci2,int lenth2,int *ans,int *asci,int *alenth);//加,减
void div(int num1[],int sci1,int lenth1,int num2[],int sci2,int lenth2,int *ans,int *asci,int *alenth);//除
void mul(int num1[],int sci1,int lenth1,int num2[],int sci2,int lenth2,int *ans,int *asci,int *alenth);//乘
void check();

int main(int argc,char *argv[])
{
    if(valid(argc,argv))
    {
        printf("%s %s %s = ",argv[1],argv[2],argv[3]);
        getnum(num1,&sci1,&lenth1,argv[1]);
        getnum(num2,&sci2,&lenth2,argv[3]);

        if(argv[2][0]=='+')
        {
            add(num1,sci1,lenth1,num2,sci2,lenth2,ans,&asci,&alenth);
        }
        else if(argv[2][0]=='-')
        {
            num2[0]*=-1;
            add(num1,sci1,lenth1,num2,sci2,lenth2,ans,&asci,&alenth);
        }
        else if(argv[2][0]=='*')
        {
            mul(num1,sci1,lenth1,num2,sci2,lenth2,ans,&asci,&alenth);
        }
        else if(argv[2][0]=='/')
        {
            int notzero;
            for(int i=1; i<=lenth2; i++)
            {
                if(num2[i]!=0)
                {
                    notzero=1;
                    break;
                }
            }
            if(notzero)
            {
                div(num1,sci1,lenth1,num2,sci2,lenth2,ans,&asci,&alenth);
            }
            else
            {
                printf("A number cannot be divied by zero.\n");
                return 0;
            }
        }
        output();
    }
    return 0;
}

int notnum(char *p)
{
    int num=0,dot=0,e=0;//检查num,dot,e是否出现过
    int i=0;

    if(p[i]=='-') i++;
    if(p[i]=='0' && p[i+1]<='9' && p[i+1]>='0')
    {
        return 1;
    }
    while(p[i]!='\0')
    {
        if(p[i]<='9' && p[i]>='0') num=1;
        else if(p[i]=='.')
        {
            if(num==0 || dot==1 || p[i+1]>'9' || p[i+1]<'0')
            {
                return 1;
            }
            dot=1; num=0;
        }
        else if(p[i]=='e')
        {
            if(num==0)
            {
                return 1;
            }
            i++; e=1;
            break;
        }
        else
        {
            return 1;
        }
        i++;
    }
    if(e==1)
    {
        if(p[i]=='-') i++;
        if((p[i]=='0' && p[i+1]!='\0') || p[i]=='\0')
        {
            return 1;
        }
        while(p[i]!='\0')
        {
            if(p[i]>'9' || p[i]<'0')
            {
                return 1;
            }
            i++;
        }
    }
    return 0;
}
void check()
{
    printf("%d %d\n",sci1,lenth1);
    if(num1[0]==-1) printf("-");
    for(int i=1; i<=lenth1; i++) printf("%d",num1[i]);
    printf("\n\n");
    printf("%d %d\n",sci2,lenth2);
    if(num2[0]==-1) printf("-");
    for(int i=1; i<=lenth2; i++) printf("%d",num2[i]);
    printf("\n\n");
}
int valid(int num,char **p)
{
    if(num!=4)
    {
        printf("Input format:number symbol number\n");
        return 0;
    }
    if((p[2][0]!='+' && p[2][0]!='-' && p[2][0]!='*' && p[2][0]!='/') || p[2][1]!='\0')
    {
        printf("Symbol:+,-,'*'(for *),/\n");
        return 0;
    }
    if(notnum(p[1]) || notnum(p[3]))
    {
        printf("The input cannot be interpret as numbers!\n");
        return 0;
    }
    return 1;
}
void getnum(int*num,int *osci,int *olenth,char *p)
{
    int sci=0,lenth=0;
    num[0]=1;
    int i=0;
    if(p[i]=='-')
    {
        num[0]=-1;
        i++;
    }
    int dot=0,sci2=0;
    while(p[i]!='e' && p[i]!='\0')
    {
        if(p[i]=='.')
        {
            dot=1; i++;
            continue;
        }
        lenth++;
        if(dot==1) sci2--;
        num[lenth]=p[i]-'0';
        i++;
    }

    if(p[i]=='e')
    {
        int k=i+1; int sym=1;//sym:科学计数法的符号

        if(p[k]=='-')
        {
            sym=-1;
            k++;
        }

        while(p[k]!='\0')
        {
            sci=sci*10+p[k]-'0';
            k++;
        }

        sci*=sym;
    }
    *osci=sci+sci2; *olenth=lenth;
}
void output()
{
    int zero=1,start=0;
    for(int i=1; i<=alenth; i++)
    {
        if(ans[i]!=0)
        {
            zero=0;
        }
    }
    if(zero)
    {
        printf("0\n");
        return;
    }
    while(ans[alenth]==0)
    {
        alenth--;
        asci++;
    }
    if(ans[0]==-1)
    {
        printf("-");
        ans[0]=0;
    }

    ans[0]=ans[1]/10;
    ans[1]%=10;

    while(ans[start]==0)
    {
        start++;
        alenth--;
    }

    int *outans=&ans[start];

    if(alenth>50)
    {
        if(outans[51]>=5)
        {
            outans[50]++;
            int i=50;
            while(outans[i]>=10 && i>0)
            {
                outans[i]-=10;
                outans[i-1]++;
                i--;
            }
        }
    }

    int preDot=alenth+asci;
    
    if(preDot>30 || preDot<-30)//使用科学计数法
    {
        asci+=alenth;
        printf("%d.",outans[0]);
        if(alenth>50) alenth=50;
        if(alenth==0)
        {
            printf("0");
        }
        for(int i=1; i<=alenth; i++)
        {
            printf("%d",outans[i]);
        }
        if(asci!=0)
        {
            printf("e%d",asci);
        }
    }
    else//不使用
    {
        if(asci>=0)//长度不会超过30
        {
            int k=alenth+asci+1;
            for(int i=0; i<=alenth; i++)
            {
                printf("%d",outans[i]);
                k--;
                if(k && k%3==0)
                {
                    printf(",");
                }
            }
            for(int i=1; i<=asci; i++)
            {
                printf("0");
                k--;
                if(k && k%3==0)
                {
                    printf(",");
                }
            }
        }
        else if(asci<0)
        {
            int dotAt=asci+alenth;//在[-30,30]
            if(alenth>50) alenth=50;
            if(dotAt<0)
            {
                printf("0.");
                dotAt++;
                for(int i=dotAt; i<0; i++) printf("0");
                for(int i=0; i<=alenth; i++) printf("%d",outans[i]);
            }
            else
            {
                int k=dotAt+1;
                for(int i=0; i<=alenth; i++)
                {
                    printf("%d",outans[i]);
                    if(i<dotAt)
                    {
                        k--;
                        if(k && k%3==0)
                        {
                            printf(",");
                        }
                    }
                    if(i==dotAt)
                    {
                        printf(".");
                    }
                }
            }
        }
    }
    printf("\n");
}
void div(int num1[],int sci1,int lenth1,int num2[],int sci2,int lenth2,int *ans,int *asci,int *alenth)
{
    int osci=0,olenth=0;
    olenth=2000+lenth2-1;
    osci=sci1-sci2+lenth1-olenth;
    ans[0]=num1[0]*num2[0];
    for(int i=1; i<=2000; i++)
    {
        int ctn=1;
        while(ctn)
        {
            for(int j=1; j<=lenth2; j++)
            {
                if(num1[i+j-1]>num2[j])
                {
                    break;
                }
                if(num1[i+j-1]<num2[j])
                {
                    ctn=0;
                    break;
                }
            }
            if(ctn)
            {
                ans[i+lenth2-1]++;
                for(int j=1; j<=lenth2; j++)
                {
                    num1[i+j-1]-=num2[j];
                    if(num1[i+j-1]<0)
                    {
                        int k=i+j-1;
                        while(num1[k]<0)
                        {
                            num1[k]+=10;
                            num1[k-1]--;
                            k--;
                        }
                    }
                }
            }
        }
        num1[i+1]+=num1[i]*10;
    }
    *asci=osci;
    *alenth=olenth;
}
void add(int num1[],int sci1,int lenth1,int num2[],int sci2,int lenth2,int *ans,int *asci,int *alenth)
{
    int maxi=lenth1+sci1;
    if(lenth2+sci2>maxi) maxi=lenth2+sci2;//最高位
    int mini=maxi-sci1;
    if(maxi-sci2>mini) mini=maxi-sci2;

    for(int i=1; i<=lenth1; i++)
    {
        ans[maxi-(sci1+lenth1-i)]+=num1[i]*num1[0];
    }
    for(int i=1; i<=lenth2; i++)
    {
        ans[maxi-(sci2+lenth2-i)]+=num2[i]*num2[0];
    }

    for(int i=mini; i>=2; i--)
    {
        if(ans[i]>=10)
        {
            ans[i]-=10;
            ans[i-1]++;
        }
        if(ans[i]<0)
        {
            ans[i]+=10;
            ans[i-1]--;
        }
    }

    for(int i=1; i<=mini; i++)
    {
        if(ans[i]!=0)
        {
            if(ans[i]<0)//第一个数字是负数
            {
                ans[0]=-1;
                for(int j=i; j<=mini; j++)
                {
                    ans[j]=-ans[j];
                    int k=j;
                    while(ans[k]<0)
                    {
                        ans[k-1]--;
                        ans[k]+=10;
                        k--;
                    }
                }
            }
            break;
        }
    }
    *alenth=mini; *asci=maxi-mini;
}

void mul(int num1[],int sci1,int lenth1,int num2[],int sci2,int lenth2,int *ans,int *asci,int *alenth)
{    
    *asci=sci1+sci2;
    *alenth=lenth1+lenth2-1;
    ans[0]=num1[0]*num2[0];
    for(int i=1; i<=lenth1; i++)
    for(int j=1; j<=lenth2; j++)
    {
        ans[i+j-1]+=num1[i]*num2[j];
    }
    for(int i=lenth1+lenth2-1; i>=2; i--)
    {
        if(ans[i]>=10)
        {
            ans[i-1]+=ans[i]/10;
            ans[i]%=10;
        }
    }
}