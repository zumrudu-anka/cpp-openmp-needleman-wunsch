#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <omp.h>
using namespace std;

float const match=3.621354295;
float const missmatch=-2.451795405;
float const gap=-1.832482334;

float *scores=new float[4999*5000*3/2];

int partition(int p, int r){
    float tmp,tmp2,tmp3;
    float x = scores[r];
    int i = p - 3;

    for(int j=p; j<=r-3; j+=3)
    {
        if(scores[j]<=x)
        {
            i+=3;
            tmp=scores[i];
            tmp2=scores[i+1];
            tmp3=scores[i+2];
            scores[i]=scores[j];
            scores[i+1]=scores[j+1];
            scores[i+2]=scores[j+2];
            scores[j]=tmp;
            scores[j+1]=tmp2;
            scores[j+2]=tmp3;
        }
    }
    tmp=scores[i+3];
    tmp2=scores[i+3+1];
    tmp3=scores[i+3+2];
    scores[i+3]=scores[r];
    scores[i+3+1]=scores[r+1];
    scores[i+3+2]=scores[r+2];
	scores[r]=tmp;
	scores[r+1]=tmp2;
	scores[r+2]=tmp3;
    return i+3;
}

void quickSort(int p, int r){
    float q;
    if(p<r)
    {
        q=partition(p, r);
        quickSort(p, q-3);
        quickSort(q+3, r);
    }
}

string EditTime(tm* coming_time){
	stringstream ss;
	ss<<"Tarih: ";
	if(coming_time->tm_mday < 10){
		ss<<"0"<<coming_time->tm_mday<<".";
	}
	else{
		ss<<coming_time->tm_mday<<".";
	}
	if(coming_time->tm_mon + 1 < 10){
		ss<<"0"<<coming_time->tm_mon + 1<<".";
	}
	else{
		ss<<coming_time->tm_mon + 1<<".";
	}
	ss<<coming_time->tm_year + 1900<<"\t"<<"Saat: ";
	if(coming_time->tm_hour < 10){
		ss<<"0"<<coming_time->tm_hour<<":";
	}
	else{
		ss<<coming_time->tm_hour<<":";
	}
	if(coming_time->tm_min < 10){
		ss<<"0"<<coming_time->tm_min<<":";
	}
	else{
		ss<<coming_time->tm_min<<":";
	}
	if(coming_time->tm_sec < 10){
		ss<<"0"<<coming_time->tm_sec;
	}
	else{
		ss<<coming_time->tm_sec;
	}
	return ss.str();
}

string GetTime(){
	time_t zaman=time(0);
	tm* simdiki_zaman = localtime(&zaman);
	return EditTime(simdiki_zaman);
}


int main(){
	
	cout<<endl<<setw(35)<<"Process Started"<<endl;
	cout<<endl<<setw(39)<<GetTime()<<endl<<endl<<endl;
	cout<<setw(46)<<"Process in Progress, please wait..."<<endl;
	
	string sequence_arrays[5000];
	ifstream sequencefile("Sequences//5K_Sequence.fasta");
	
	string temp;
	getline(sequencefile,temp);
	int count=0;
	while(!sequencefile.eof()){
		getline(sequencefile,temp);
		getline(sequencefile,temp);	
		getline(sequencefile,sequence_arrays[count]);
		count++;
	}
	sequencefile.close();
	
	int scores_count=0;
	omp_set_num_threads(32);
	#pragma omp parallel for
	for(int i=0;i<4999;i++){
		for(int j=i+1;j<5000;j++){
			float compare_matrix[201][201];
			compare_matrix[0][0]=0;
			float gap2=gap;
			for(int k=1;k<201;k++){
				compare_matrix[0][k]=gap2;
				compare_matrix[k][0]=gap2;
				gap2+=gap;
			}
			for(int k=1;k<201;k++){
				for(int t=1;t<201;t++){
					// Match
					if(sequence_arrays[i][k]==sequence_arrays[j][t]){
						compare_matrix[k][t] = max((compare_matrix[k-1][t-1]+match),max((compare_matrix[k-1][t]+gap),(compare_matrix[k][t-1]+gap)));
					}
					// Missmatch
					else{
						compare_matrix[k][t] = max((compare_matrix[k-1][t-1]+missmatch),max((compare_matrix[k-1][t]+gap),(compare_matrix[k][t-1]+gap)));
					}
				}
			}
			#pragma omp critical
			{
				scores[scores_count*3]=compare_matrix[200][200];
				scores[scores_count*3+1]=i;
				scores[scores_count*3+2]=j;
				scores_count++;
			}
			
		}
	}
			
	quickSort(0,(scores_count*3-3));
	
	ofstream result_file("1000Results.txt");
	
	result_file<<endl<<setw(70)<<"SKOR TABLOSU"<<endl<<endl<<endl;
    result_file<<setw(47)<<"No"<<setw(10)<<"S1"<<setw(10)<<"S2"<<setw(15)<<"Skor"<<endl;
    result_file<<setw(86)<<"--------------------------------------------"<<endl;
	count=1;
	for(int i=scores_count*3-3;i>scores_count*3-63;i-=3){
		result_file<<setw(47)<<count<<setw(10)<<scores[i+1]<<setw(10)<<scores[i + 2]<<setw(17)<<scores[i]<<endl;
		count++;
	}
	result_file.close();
	
	cout<<endl<<endl<<endl<<setw(34)<<"Process Done"<<endl;
	cout<<endl<<setw(39)<<GetTime()<<endl;
	
	return 0;
}
