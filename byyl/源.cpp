#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define	LENGTH 46
#define N 100
//************************
typedef struct token
{
	char name[30];
	int code;
	int addr;
}token;

typedef struct KeyWord
{
	char name[30];
	int code;
}KeyWord;

typedef struct symble
{
	char name[30];//�ַ�����
	int number;//�ַ�����
	int type;
}symble;

//**********************************
char ch;
int error_count; //������ֵĸ���
int var_count;   //
int num_count;   //
int label_count;
int code_count;  //
int addr_count;  //�����ַ
int LineOfPro;   //������ֵ��к�
char filename[30];
FILE *SourceFin;    //Դ�ļ�
FILE *TokenFout;    //����ļ�
FILE *SymbleFout;   //���ű�
FILE *NumFout;   //������

KeyWord key[14] = { {"void",1},{"main",2},{"int",3},{"float",4},{"const",5},{"for",6},
{"if",7},{"else",8},{"then",9},{"while",10},{"switch",11},{"break",12},{"begin",13},{"end",14} };

token CurrentToken;
token zancun;
symble CurrentSimble;
symble SymbleList[N];
symble NumList[N];
//***********************************
void Scanner();       //������
void IsAlpha();       //�ؼ���
void IsNumber();      //����
void IsAnotation();   //ע��
void IsOther();       //����
void OutPut();        //���
void Error(int a);    //��������
int Flag_WordHave();  //������ű�
int Flag_NumHave();   //��������
//*************************************
int main()
{
	int i = 0, j = 0;
	code_count = 0;
	var_count = 1;
	label_count = 1;
	addr_count = 0;
	num_count = 0;
	LineOfPro = 0; //�к�
	Scanner();
	printf("�����ʶ����\n");
	for (i = 0; i < var_count - 1; i++)
		printf("<%s,%d>", SymbleList[i].name, i + 1);
	printf("\n");
	printf("������ֱ�\n");
	for (i = 0; i < num_count; i++)
		printf("<%s,%d>", NumList[i - 1].name, i + 1);
	return 0;
}
//*************������***************
void Scanner()
{
	int i = 0;
	if ((SourceFin = fopen("C:\\Users\\ASUS\\Desktop\\cin.txt", "r")) == NULL)
	{
		printf("�޷����ļ�%s!\n", filename);
		exit(1);
	}

	if ((TokenFout = fopen("C:\\Users\\ASUS\\Desktop\\cout.txt", "w")) == NULL)
	{
		printf("�޷����ļ�����ļ�.txt��\n");
		exit(1);
	}
	if ((SymbleFout = fopen("C:\\Users\\ASUS\\Desktop\\�����ļ�.txt", "w")) == NULL)
	{
		printf("�޷��򿪷����ļ�.txt��\n");
		exit(1);
	}
	if ((NumFout = fopen("C:\\Users\\ASUS\\Desktop\\�����ļ�.txt", "w")) == NULL)
	{
		printf("�޷����ļ�����.txt��\n");
		exit(1);
	}
	ch = fgetc(SourceFin);
	while (ch != EOF)
	{
		for (i = 0; i < 30; i++)
			CurrentToken.name[i] = '\0';//�����ʻ�������ʼ��
		if ((ch > 47) && (ch < 58))
			IsNumber();
		if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (
			ch <= 'Z')) || (ch == '_'))
		{
			IsAlpha();
		}
		if (ch == '/')
			IsAnotation();
		else
			IsOther();
	}
	fclose(TokenFout);
	fclose(SymbleFout);
	fclose(NumFout);
	printf("�ʷ�������ϡ�\n");
}

//************���ִ���****************
void IsNumber()
{
	int k = 0;
	while (((ch >= '0') && (ch <= '9')))
	{
		CurrentToken.name[k++] = ch;//�����ַ��뵥�ʻ�����
		ch = fgetc(SourceFin);

	}
	CurrentToken.code = 18;//���ֵĻ�������18
	OutPut();
}
//************�Ƿ�Ϊ�ؼ���****************
void IsAlpha()
{
	int i, h;
	h = 0;
	i = 0;
	while (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')) || ch == '_')//�������ĵ��ʷ��뵥�ʻ�����
	{
		CurrentToken.name[i++] = ch;
		ch = fgetc(SourceFin);
	}
	zancun = CurrentToken;
	for (i = 0; i < 14; i++)//�����ʻ������еĴʺ͹ؼ��������еĴʱȽϣ����ǲ��ǹؼ���
	{
		for (int j = 0; j < 30; j++)
		{
			if (CurrentToken.name[j] == key[i].name[j])
				h = 0;
			else
			{
				h = 1; break;
			}

		}
		if (h == 0)
			break;
	}
	if (h == 0)
	{
		CurrentToken.code = key[i].code;//����i���ؼ��ֵĻ���������ʻ����������е��ʵĻ�����
		CurrentToken.addr = -1;//�ؼ��ֵ�ַΪ-1
		OutPut();
	}
	else
	{
		CurrentToken.code = 17;
		CurrentToken.addr = addr_count++;	//������ǹؼ��־�����ͨ��ʶ������ַ�ӣ�
		OutPut();
	}
}
//**************����ע��*****************
void IsAnotation()
{
	char ch1;
	ch1 = ch;
	ch = fgetc(SourceFin);
	if (ch == '*')
	{
		for (;;)
		{
			ch = fgetc(SourceFin);
			if (ch == EOF)
			{
				Error(2); break;
			}//�����û��*˵��ע�Ͳ���ȫ���д���
			if (ch == '*')
			{
				ch1 = ch;
				ch = fgetc(SourceFin);
				if (ch == '/')//��������*/˵��ע������
				{
					ch = fgetc(SourceFin); break;
				}
			}
		}
	}
	else
	{
		error_count++;
		Error(2);
		CurrentToken.name[0] = '/';//���ע�Ͳ�����������һ����ĸ����/
		CurrentToken.code = 22;
		CurrentToken.addr = -1;//���ŵĵ�ַ��-1
		OutPut();
	}
}

//***************���� ************       
void IsOther()
{
	char ch1;
	int i;
	for (i = 0; i < 30; i++)
	{
		CurrentToken.name[i] = '\0';
	}//����������ʼ��
	switch (ch)
	{
	case'+':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '+';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 38;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = '+';
			CurrentToken.code = 19;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'-':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '-';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 39;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = '-';
			CurrentToken.code = 20;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'*':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '*';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 40;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = '*';
			CurrentToken.code = 21;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'%':
	{
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '%';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 41;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = '%';
			CurrentToken.code = 23;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'(':
	{
		CurrentToken.name[0] = '(';
		CurrentToken.code = 24;
		CurrentToken.addr = -1;
		OutPut();
		ch = fgetc(SourceFin);
		break;
	}
	case')':
	{
		CurrentToken.name[0] = ')';
		CurrentToken.code = 25;
		CurrentToken.addr = -1;
		OutPut();
		ch = fgetc(SourceFin);
		break;
	}
	case'[':
	{
		CurrentToken.name[0] = '[';
		CurrentToken.code = 26;
		CurrentToken.addr = -1;
		OutPut();
		ch = fgetc(SourceFin);
		break;
	}
	case']':
	{
		CurrentToken.name[0] = ']';
		CurrentToken.code = 27;
		CurrentToken.addr = -1;
		OutPut();
		ch = fgetc(SourceFin);
		break;
	}
	case'<':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '<';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 31;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = '<';
			CurrentToken.code = 29;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'>':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '>';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 32;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = '>';
			CurrentToken.code = 30;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'=':
	{
		CurrentToken.name[0] = '=';
		CurrentToken.code = 33;
		CurrentToken.addr = -1;
		OutPut();
		ch = fgetc(SourceFin);
		break;
	}
	case'!':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '=')
		{
			CurrentToken.name[0] = '!';
			CurrentToken.name[1] = '=';
			CurrentToken.code = 34;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
		else
		{
			CurrentToken.name[0] = 'n';
			CurrentToken.name[1] = 'o';
			CurrentToken.name[2] = 't';
			CurrentToken.code = 44;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case';':
	{
		CurrentToken.name[0] = ';';
		CurrentToken.code = 35;
		CurrentToken.addr = -1;
		OutPut();
		ch = fgetc(SourceFin);
		break;
	}
	case'|':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '|')
		{
			CurrentToken.name[0] = 'O';
			CurrentToken.name[1] = 'R';
			CurrentToken.code = 42;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case'&':
	{
		ch1 = fgetc(SourceFin);
		if (ch1 == '&')
		{
			CurrentToken.name[0] = 'A';
			CurrentToken.name[1] = 'N';
			CurrentToken.name[2] = 'D';
			CurrentToken.code = 43;
			CurrentToken.addr = -1;
			OutPut();
			ch = fgetc(SourceFin);
			break;
		}
	}
	case 10:                //    /n����
	{
		LineOfPro++;
		ch = fgetc(SourceFin);
		break;
	}
	case 13:                 //   �س�����
	{
		LineOfPro++;
		ch = fgetc(SourceFin);
		break;
	}
	case' ':                 //     �ո�
		CurrentToken.code = 60;
		ch = fgetc(SourceFin);
		break;

	default:Error(1);
		ch = fgetc(SourceFin);
		break;
	}
}
//************��������************
void Error(int a)
{
	error_count++;
	switch (a)
	{
	case 1:
	{printf("error %2d �Ƿ��ַ� %3d��.\n", error_count, LineOfPro + 1); break; }

	case 2:
	{printf("error %2d û��ƥ���ע�ͷ� %3d��.\n", error_count, LineOfPro + 1); break; }

	}
	return;
}
void OutPut()
{
	int i = 0;
	//�����ʽ
	if (CurrentToken.code == 17)         //��־�����
	{
		CurrentSimble.number = CurrentToken.addr;
		CurrentSimble.type = CurrentToken.code;
		strcpy(CurrentSimble.name, CurrentToken.name);
		Flag_WordHave();
		fprintf(TokenFout, "<id,%d>", addr_count);
		printf("<id,%d>", addr_count);
	}
	else
		if (CurrentToken.code == 18)         //   �������
		{
			CurrentSimble.number = CurrentToken.addr;
			CurrentSimble.type = CurrentToken.code;
			strcpy(CurrentSimble.name, CurrentToken.name);
			Flag_NumHave();
			fprintf(TokenFout, "<num , %s>", CurrentToken.name);
			printf("<num , %d>", num_count);

		}
		else
			if ((CurrentToken.code >= 1) && (CurrentToken.code <= 14))//�ؼ��ֵ����
			{
				fprintf(TokenFout, "<%s,_>", zancun.name);
				printf("<%s ,_>", zancun.name);
			}
			else//���ŵ����
			{
				fprintf(TokenFout, "<%s,_>", CurrentToken.name);
				printf("<%s ,_>", CurrentToken.name);
			}
}
//�������
int Flag_WordHave()
{
	int flag, i = 0;
	//�û�����ű��еķ��źͷ��������еıȽ�
	for (i = 0; i < (var_count - 1); i++)
	{
		flag = strcmp(CurrentSimble.name, SymbleList[i].name);
		if (flag == 0)
		{
			CurrentToken.addr = var_count;//������ڣ�����������ĵ�ַ����
			return 0;
		}
	}
	SymbleList[var_count - 1].number = CurrentToken.addr;
	SymbleList[var_count - 1].type = CurrentToken.code;
	strcpy(SymbleList[var_count - 1].name, CurrentToken.name);//������д��
	fprintf(SymbleFout, "<%s ,%3d >", SymbleList[var_count - 1].name, var_count);//���ŵ����ģʽ
	printf("<%s ,%3d >", SymbleList[var_count - 1].name, var_count);
	var_count = var_count + 1;
	return 1;
}

//����
int Flag_NumHave()
{
	int flag, i = 0;
	//�û��峣�����еĳ����ͳ��������еıȽ�
	for (i = 0; i < (num_count - 1); i++)
	{
		flag = strcmp(CurrentSimble.name, NumList[i].name);
		if (flag == 0)
		{
			CurrentToken.addr = num_count;//������ڣ�����������ĵ�ַ����
			return 0;
		}
	}
	NumList[num_count - 1].number = CurrentToken.addr;
	NumList[num_count - 1].type = CurrentToken.code;
	strcpy(NumList[num_count - 1].name, CurrentToken.name);//������д��
	fprintf(NumFout, "<%s ,%3d >", NumList[num_count - 1].name, num_count);//���ŵ����ģʽ
	num_count = num_count + 1;
	return 1;
}
