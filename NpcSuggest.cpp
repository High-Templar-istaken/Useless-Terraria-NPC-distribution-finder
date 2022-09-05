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
	建议在windows下编译本程序\n\
	本程序最多支持30个NPC和30种环境\n\
	指令文件由三个部分组成：环境列表，NPC需求，目标要求\n\
	每个部分之间用一个等于号间隔开\n\
	以下为正文：\n\
	-----------------------------------------\n\
	环境列表中使用者要列出所有环境的名字，\n\
	每个名字要由空格隔开，并且只能一行\n\
	例：地表蘑菇地 森林\n\
	-----------------------------------------\n\
	用一个\"=\"告诉程序本部分程序结束\n\
	-----------------------------------------\n\
	NPC需求中使用者输入每一个NPC的要求，建议从同目录下的npclistcode.txt中进行粘贴，注意一定要分三行，分别介绍名字，环境喜好和NPC喜好\n\
	例：\n\
	工具人\n\
	+贴吧-4399\n\
	+路人-空气人\n\
	-----------------------------------------\n\
	用一个\"=\"告诉程序本部分程序结束\n\
	-----------------------------------------\n\
	目标要求由多行表达式组成，每一行格式均为 NPC名字 + 运算符 + 数字，其中后面的表达式与前面的表达式冲突时，已后面的表达式为准\n\
	运算符: > < !，其中!代表不做要求\n\
	-----------------------------------------\n\
	用一个\"=\"告诉程序本部分程序结束\n\
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
			color(14);printf("环境列表读取完成\n");
			return;
		}
		INTtoENV[++totenv]=tmp;
		ENVtoINT[tmp]=totenv;
		if(debug) cout<<"DEBUG:\t环境加入"<<tmp<<" as:"<<totenv<<endl;
	}
} 

inline void check(string name)
{
	if(NAMEtoINT[name]==0)
	{
		INTtoNAME[++totnpc]=name;
		NAMEtoINT[name]=totnpc;
		if(debug) cout<<"DEBUG:\tNPC加入"<<name<<" as:"<<totnpc<<endl;
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
				color(11);printf("NPC需求读取完成\n");	
				if(debug) for(int i=1;i<=totnpc;++i) cout<<INTtoNAME[i]<<" as "<<i<<endl;
				return;
			}
			if(npcname!="\n") break;
		}
		check(npcname);
		req>>envlist>>npclist;
		if(debug) cout<<"------------\nDEBUG:\n"<<"对于:\t"<<npcname<<"\n环境:\t"<<envlist<<"\nNPC:\t"<<npclist<<"\n------------\n";
		
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
			if(debug) cout<<"DEBUG:\tNPC"<<NAMEtoINT[npcname]<<"对于"<<ENVtoINT[envname]<<"+="<<tmp<<endl;
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
			if(debug) cout<<"DEBUG:\tNPC"<<NAMEtoINT[npcname]<<"对于"<<NAMEtoINT[anothernpcname]<<"+="<<tmp<<endl;
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
		if(npcname=="全体")
		{
			for(int j=1;j<=totnpc;++j)
			{
				npchappy[j]=num;
				happy[j]=(oper==">"?1:0);
			}
		}
		else if(NAMEtoINT[npcname]==0)
		{
			cout<<"警告！未知的NPC："<<npcname<<endl;
		}
		else
		{
			npchappy[NAMEtoINT[npcname]]=num;
			happy[NAMEtoINT[npcname]]=(oper==">"?1:0);
		}
	}
	if(debug)
	{
		cout<<"------------\nDEBUG:\n注：-121296即不做要求\n";
		for(int j=1;j<=totnpc;++j) cout<<INTtoNAME[j]<<(happy[j]==1?">":"<")<<npchappy[j]<<endl;
		cout<<"------------\n";
	}
	
	printf("要求列表读取完成\n");
}

int envuse[31],envhave[31][31],npcin[31],nowhappy[31];
string SB="蘑菇人",SBlive="蘑菇地";

void judge()
{
    if(debug)
	{
	//	getchar();
		for(int i=1;i<=totenv;++i)
		{
			cout<<"在环境 "<<INTtoENV[i]<<"中：";
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
		if(debug) cout<<"对于NPC:"<<INTtoNAME[i]<<"快乐值为:"<<nowhappy[i]<<endl;
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
		sol<<"在环境 "<<INTtoENV[i]<<"中：";
		for(int j=1;j<=envuse[i];++j)
		{
			sol<<INTtoNAME[envhave[i][j]]<<" ";
		}
		sol<<endl<<endl;
		
	}
	cout<<"有解！"<<endl;
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
	printf("正在求解...\n");
	dfs(1);
}

int main()
{
	color(2);
	printf("欢迎使用泰拉瑞亚NPC快乐值求解程序\n");
	color(12);
	printf("兴趣之作，技术有限还请谅解。\n");printf("程序在terraria百度贴吧开源发布。\n"); 
	printf("所使用算法为暴力枚举:(\n");
	printf("本程序对requests.txt有严格的要求，请务必遵守，不然会出现意想不到的错误\n");
	color(9);
	
	string run="";
	while(true)
	{
		printf("输入help获取帮助，输入limit关闭/开启同一生物群系最多4人限制，输入debug显示/关闭调试信息，输入go可开始求解:");
		getline(cin,run);
		if(run=="help")
		{
			gethelp();
			color(12);
			printf("帮助已输出\n");
			color(13);
		}
		else if(run=="go")
		{
			solve();
			color(12);
			printf("求解完成！结果已经放置在程序同目录下的solutions.txt文件中！\n");
			color(13);printf("感谢使用！按任意键退出程序\n");
			getchar();
			color(7);
			exit(0);
		}
		else if(run=="debug")
		{
			debug=!debug;
			color(8);
			if(debug) printf("debug已开启，debug输出将耗费大量运行时间！\n");
			else printf("debug已关闭\n");
			color(9);
		}
		else if(run=="limit")
		{
			limit=!limit;
			color(8);
			if(limit) printf("limit已开启\n");
			else printf("limit已关闭，运行时间将极长！\n");
			color(9);
		}
		else
		{
			color(11);
			printf("未识别的指令\n");
			color(9);
		}
	}
	return 0;
} 
