#include<bits/stdc++.h>
#include <windows.h>
using namespace std;
bool debug=0,limit=1,ans=0;
ifstream req("requests.txt");
ofstream sol("solutions.txt");
string s;

void color(int x)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

void gethelp()
{
	ofstream he("help.txt");
	he<<"\
	������windows�±��뱾����\n\
	���������֧��30��NPC��30�ֻ���\n\
	ָ���ļ�������������ɣ������б�NPC����Ŀ��Ҫ��\n\
	ÿ������֮����һ�����ںż����\n\
	����Ϊ���ģ�\n\
	-----------------------------------------\n\
	�����б���ʹ����Ҫ�г����л��������֣�\n\
	ÿ������Ҫ�ɿո����������ֻ��һ��\n\
	�����ر�Ģ���� ɭ��\n\
	-----------------------------------------\n\
	��һ��\"=\"���߳��򱾲��ֳ������\n\
	-----------------------------------------\n\
	NPC������ʹ��������ÿһ��NPC��Ҫ�󣬽����ͬĿ¼�µ�npclistcode.txt�н���ճ����ע��һ��Ҫ�����У��ֱ�������֣�����ϲ�ú�NPCϲ��\n\
	����\n\
	������\n\
	+����-4399\n\
	+·��-������\n\
	-----------------------------------------\n\
	��һ��\"=\"���߳��򱾲��ֳ������\n\
	-----------------------------------------\n\
	Ŀ��Ҫ���ɶ��б��ʽ��ɣ�ÿһ�и�ʽ��Ϊ NPC���� + ����� + ���֣����к���ı��ʽ��ǰ��ı��ʽ��ͻʱ���Ѻ���ı��ʽΪ׼\n\
	�����: > < !������!������Ҫ��\n\
	-----------------------------------------\n\
	��һ��\"=\"���߳��򱾲��ֳ������\n\
	-----------------------------------------\n\
	";
}

map<int,string> INTtoENV;
map<string,int> ENVtoINT;
map<int,string> INTtoNAME;
map<string,int> NAMEtoINT;
int totenv=0,totnpc=0;
int npcTOenv[31][31];
int npcTOnpc[31][31];
int npchappy[31];
bool happy[31];

void enviourments_read()
{
	string tmp;
	while(true)
	{
		req>>tmp;
		if(tmp=="=")
		{
			color(14);printf("�����б��ȡ���\n");
			return;
		}
		INTtoENV[++totenv]=tmp;
		ENVtoINT[tmp]=totenv;
		if(debug) cout<<"DEBUG:\t��������"<<tmp<<" as:"<<totenv<<endl;
	}
} 

inline void check(string name)
{
	if(NAMEtoINT[name]==0)
	{
		INTtoNAME[++totnpc]=name;
		NAMEtoINT[name]=totnpc;
		if(debug) cout<<"DEBUG:\tNPC����"<<name<<" as:"<<totnpc<<endl;
	}
}
inline int isval(char c)
{
	if(c=='-') return -1;
	if(c=='+') return 1;
	return 0;
}

void npc_read()
{
	string npcname,envlist,npclist;
	while(true)
	{
		while(req>>npcname)
		{
			if(npcname=="=")
			{
				color(11);printf("NPC�����ȡ���\n");	
				if(debug) for(int i=1;i<=totnpc;++i) cout<<INTtoNAME[i]<<" as "<<i<<endl;
				return;
			}
			if(npcname!="\n") break;
		}
		check(npcname);
		req>>envlist>>npclist;
		if(debug) cout<<"------------\nDEBUG:\n"<<"����:\t"<<npcname<<"\n����:\t"<<envlist<<"\nNPC:\t"<<npclist<<"\n------------\n";
		
		int tmp=0;
		string envname="",anothernpcname="";
		for(int i=0;i<envlist.size();)
		{
			while(i<envlist.size()&&isval(envlist[i])!=0)
			{
				tmp+=isval(envlist[i]);
				++i;
			}
			while(i<envlist.size()&&isval(envlist[i])==0)
			{
				envname=envname+envlist[i];
				++i;
			}
			npcTOenv[NAMEtoINT[npcname]][ENVtoINT[envname]]+=tmp;
			if(debug) cout<<"DEBUG:\tNPC"<<NAMEtoINT[npcname]<<"����"<<ENVtoINT[envname]<<"+="<<tmp<<endl;
			tmp=0;envname="";
		}
		
		for(int i=0;i<npclist.size();)
		{
			while(i<npclist.size()&&isval(npclist[i])!=0)
			{
				tmp+=isval(npclist[i]);
				++i;
			}
			while(i<npclist.size()&&isval(npclist[i])==0)
			{
				anothernpcname=anothernpcname+npclist[i];
				++i;
			}
			check(anothernpcname);
			npcTOnpc[NAMEtoINT[npcname]][NAMEtoINT[anothernpcname]]+=tmp;
			if(debug) cout<<"DEBUG:\tNPC"<<NAMEtoINT[npcname]<<"����"<<NAMEtoINT[anothernpcname]<<"+="<<tmp<<endl;
			tmp=0;anothernpcname="";
		}
		
	}
	
}

void request_read()
{
	for(int j=1;j<=totnpc;++j) npchappy[j]=-121296;
	
	color(10);
	string npcname,oper,number;
	int num,i;
	while(true)
	{
		num=0,i=0;
		req>>npcname;
		if(npcname=="=") break;
		req>>oper>>number;
		
		while(i<number.size()) num=num*10+number[i++]-'0';
		if(oper=="!") num=-121296;
		if(npcname=="ȫ��")
		{
			for(int j=1;j<=totnpc;++j)
			{
				npchappy[j]=num;
				happy[j]=(oper==">"?1:0);
			}
		}
		else if(NAMEtoINT[npcname]==0)
		{
			cout<<"���棡δ֪��NPC��"<<npcname<<endl;
		}
		else
		{
			npchappy[NAMEtoINT[npcname]]=num;
			happy[NAMEtoINT[npcname]]=(oper==">"?1:0);
		}
	}
	if(debug)
	{
		cout<<"------------\nDEBUG:\nע��-121296������Ҫ��\n";
		for(int j=1;j<=totnpc;++j) cout<<INTtoNAME[j]<<(happy[j]==1?">":"<")<<npchappy[j]<<endl;
		cout<<"------------\n";
	}
	
	printf("Ҫ���б��ȡ���\n");
}

int envuse[31],envhave[31][31],npcin[31],nowhappy[31];
string SB="Ģ����",SBlive="Ģ����";

void judge()
{
    if(debug)
	{
	//	getchar();
		for(int i=1;i<=totenv;++i)
		{
			cout<<"�ڻ��� "<<INTtoENV[i]<<"�У�";
			for(int j=1;j<=envuse[i];++j)
			{
				cout<<INTtoNAME[envhave[i][j]]<<" ";
			}
			cout<<endl;
		}
	}
	
	for(int i=1;i<=totnpc;++i)
	{
		nowhappy[i]=0;
		if(NAMEtoINT[SB]==i) nowhappy[i]=-1;
		
		nowhappy[i]+=npcTOenv[i][npcin[i]];
		for(int j=1;j<=envuse[npcin[i]];++j)
		{
			if(envhave[npcin[i]][j]!=i)
			{
				nowhappy[i]+=npcTOnpc[i][envhave[npcin[i]][j]];
			}
		}
		if(envuse[i]<=4) nowhappy[i]+=2;
		if(debug) cout<<"����NPC:"<<INTtoNAME[i]<<"����ֵΪ:"<<nowhappy[i]<<endl;
		if(npchappy[i]==-121296) continue;
		if(happy[i]==1)
		{
			if(nowhappy[i]<=npchappy[i]) return;
		}
		if(happy[i]==0)
		{
			if(nowhappy[i]>=npchappy[i]) return;
		}
	}
	
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	ans=1;
	/*!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	
	for(int i=1;i<=totenv;++i)
	{
		sol<<"�ڻ��� "<<INTtoENV[i]<<"�У�";
		for(int j=1;j<=envuse[i];++j)
		{
			sol<<INTtoNAME[envhave[i][j]]<<" ";
		}
		sol<<endl<<endl;
		
	}
	cout<<"�н⣡"<<endl;
} 

void dfs(int nownpc)
{
	if(nownpc>totnpc)
	{
		judge();
		return;
	}
	
	if(nownpc==NAMEtoINT[SB])
	{
		if(limit&&envuse[ENVtoINT[SBlive]]>=4) return;
		envhave[ENVtoINT[SBlive]][++envuse[ENVtoINT[SBlive]]]=nownpc;
		dfs(nownpc+1);
		for(int j=1;j<=envuse[ENVtoINT[SBlive]]+1;++j)
		{
			if(envhave[ENVtoINT[SBlive]][j]==nownpc)
			{
				envhave[ENVtoINT[SBlive]][j]=0;
			}
			if(envhave[ENVtoINT[SBlive]][j-1]==0)
			{
				envhave[ENVtoINT[SBlive]][j-1]=envhave[ENVtoINT[SBlive]][j];
				envhave[ENVtoINT[SBlive]][j]=0;
			}
		}
		envuse[ENVtoINT[SBlive]]--;
	}
	for(int i=1;i<=totenv;++i)
	{
		if(ans==1) return;
		if(limit&&envuse[i]>=4) continue;
		envhave[i][++envuse[i]]=nownpc;
		npcin[nownpc]=i;
		
		if(limit&&envuse[i]==4)
		{
			for(int k=1;k<=4;++k)
			{
				nowhappy[envhave[i][k]]=0;
				if(INTtoNAME[envhave[i][k]]==SB) nowhappy[envhave[i][k]]=-1;
				for(int j=1;j<=4;++j)
				{
					if(envhave[i][j]!=envhave[i][k])
					{
						nowhappy[envhave[i][k]]+=npcTOnpc[envhave[i][k]][envhave[i][j]];
					}
				}
				if(happy[envhave[i][k]]==1)
				{
					if(nowhappy[envhave[i][k]]<=npchappy[envhave[i][k]]) goto CUT;
				}
				if(happy[envhave[i][k]]==0)
				{
					if(nowhappy[envhave[i][k]]>=npchappy[envhave[i][k]]) goto CUT;
				}
			}
		}
		
		dfs(nownpc+1);
		
		CUT:
		for(int j=1;j<=envuse[i]+1;++j)
		{
			if(envhave[i][j]==nownpc)
			{
				envhave[i][j]=0;
			}
			if(envhave[i][j-1]==0)
			{
				envhave[i][j-1]=envhave[i][j];
				envhave[i][j]=0;
			}
		}
		envuse[i]--;
		
	}
}

void solve()
{
	enviourments_read();
	npc_read();
	request_read();
	for(int i=1;i<=totenv;++i)
	{
		envhave[i][0]=234;
	}
	printf("�������...\n");
	dfs(1);
}

int main()
{
	color(2);
	printf("��ӭʹ��̩������NPC����ֵ������\n");
	color(12);
	printf("��Ȥ֮�����������޻����½⡣\n");printf("������terraria�ٶ����ɿ�Դ������\n"); 
	printf("��ʹ���㷨Ϊ����ö��:(\n");
	printf("�������requests.txt���ϸ��Ҫ����������أ���Ȼ��������벻���Ĵ���\n");
	color(9);
	
	string run="";
	while(true)
	{
		printf("����help��ȡ����������limit�ر�/����ͬһ����Ⱥϵ���4�����ƣ�����debug��ʾ/�رյ�����Ϣ������go�ɿ�ʼ���:");
		getline(cin,run);
		if(run=="help")
		{
			gethelp();
			color(12);
			printf("���������\n");
			color(13);
		}
		else if(run=="go")
		{
			solve();
			color(12);
			printf("�����ɣ�����Ѿ������ڳ���ͬĿ¼�µ�solutions.txt�ļ��У�\n");
			color(13);printf("��лʹ�ã���������˳�����\n");
			getchar();
			color(7);
			exit(0);
		}
		else if(run=="debug")
		{
			debug=!debug;
			color(8);
			if(debug) printf("debug�ѿ�����debug������ķѴ�������ʱ�䣡\n");
			else printf("debug�ѹر�\n");
			color(9);
		}
		else if(run=="limit")
		{
			limit=!limit;
			color(8);
			if(limit) printf("limit�ѿ���\n");
			else printf("limit�ѹرգ�����ʱ�佫������\n");
			color(9);
		}
		else
		{
			color(11);
			printf("δʶ���ָ��\n");
			color(9);
		}
	}
	return 0;
} 
