#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ResetCin() rewind(stdin)
#define isvchar(_Char) ( _Char=='_' || isdigit(_Char) || isupper(_Char) || islower(_Char) )
#define QWORD unsigned long long

void menu();
char choose(char c);

int main()
{
	char *buffer;
	char *ptr;
	int length;
	int bufsiz=0x1000;
	int getsiz=0x400;
	int bufadd=0x1000;

	int i, j, len, row;

	FILE *fp;
	char *env, *filepath, *target, *pc, *pc1, *pc2, *pc3, c;
	filepath=malloc(0x400);
	buffer=malloc(bufsiz);
	target=malloc(0x400);
	if(!filepath||!buffer||!target)
		return -1;
	*(QWORD*)buffer=0;
	ptr=buffer, length=0;
	fp=fopen(filepath, "w+");

	while(1)
	{
		menu();
		ResetCin();
		ungetc(' ', stdin);
		if( scanf("%*[^0-9a-zA-Z]%1[0-9a-zA-Z]", &i)<1 )
			continue;
		i=choose(i);
		switch(i)
		{
			case 'A':
				printf("Please enter the text(\"Ctrl+S\"end):\n");
				while(1){
					if(bufsiz-length<getsiz){
						pc=realloc(buffer, bufsiz+bufadd);
						if(!pc)
							return ~'A'+1;
						buffer=pc, bufsiz+=bufadd, ptr=buffer+length;
					}
					ResetCin();
					i=scanf("%1024[^\n]", ptr);
					ptr+=i, length+=i;
					if(i<getsiz)
						break;
				}
				putchar('\n');
				*ptr=0;
			break;
			case 'B':
				puts(buffer);
			break;
			case 'C':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				pc=buffer, j=0;
				while(pc<ptr && (pc=strstr(pc, target)))
						j++, pc++;
				printf(">>>���ҵ� %d �� \"%s\"\n\n", j, target);
			break;
			case 'D':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				i=strlen(target);
				pc=buffer, j=0;
				while(pc<ptr && (pc=strstr(pc, target))){
					if( (pc==buffer || !isvchar(*(pc-1))) && (!*(pc+i) || !isvchar(*(pc+i))) )
						j++;
					pc++;
				}
				printf(">>>���ҵ� %d �� \"%s\"\n\n", j, target);
			break;
			case 'E':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				i=0, j=0, row=1;
				pc=buffer, pc1=pc;
				while(pc=strstr(pc, target)){
					c=*pc, *pc=0;
					while(pc3=strchr(pc1, '\n'))
						row++, pc1=pc3+1;
					pc2= row>1 ? pc1-1 : pc1, j=0;
					while(pc3=strchr(pc2, '\t'))
						j++, pc2=pc3+1;
					*pc=c, i++, pc++;
					printf("%d. ��%d��, ��%d��\n", i, row, pc-pc1+j*7);
				}
				printf("���ҵ�%d�� \"%s\"\n", i, target);
			break;
			case 'F':
				printf("������Ҫ���ҵ��ַ���: ");
				ResetCin();
				ungetc('\n', stdin);
				scanf("%*[\n]%64[^\n]", target);
				i=0, j=0, row=1;
				len=strlen(target);
				pc=buffer, pc1=pc;
				while(pc=strstr(pc, target)){
					c=*pc, *pc=0;
					while(pc3=strchr(pc1, '\n'))
						row++, pc1=pc3+1;
					pc2=row>1 ? pc1-1 : pc1;
					j=0;
					if( (pc==buffer || !isvchar(*(pc-1))) && (!*(pc+len) || !isvchar(*(pc+len))) ){
						while(pc3=strchr(pc2, '\t'))
							j++, pc2=pc3+1;
						i++;
						printf("%d. ��%d��, ��%d��\n", i, row, pc-pc1+1+j*7);
					}
					*pc++=c;
				}
				printf("���ҵ�%d�� \"%s\"\n", i, target);
			break;
			case 'X':
				system("clear");
			break;
			case 'Q':
				return 0;
			break;
			default:
				printf(">>>switch case::This option was not found!\n");
		}
	}
}

void menu()
{
	printf("A.��������  B.�������  C.����  D.����ȫ��  E.��λ  F.ȫ�ʶ�λ  X.����  Q.�˳�\n��ѡ��: ");
}

char choose(char c)
{
	if(0x30<=c&&c<=0x39)
		c-=0x30;
	else if(0x41<=c&&c<=0x5a)
		c-=0x40;
	else if(0x61<=c&&c<=0x7a)
		c-=0x60;
	else
		c=-1;
	c+=0x40;
	printf(">>>��⵽ѡ��\'%c\'\n", c);
	return c;
}

