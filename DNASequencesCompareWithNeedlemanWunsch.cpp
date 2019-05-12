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

void swap(float* a, float* b) 
{ 
    float t = *a;
    *a = *b;
    *b = t;
} 

int partition(float arr[], int low, int high) 
{ 
    float pivot = arr[high];    // pivot 
    int i = (low - 3);  // En kucuk elemanin indisi 
  
    for (int j = low; j <= high- 3; j+=3)
    { 
        // Eldeki eleman pivota esit ya da kucukse...
        
        if (arr[j] <= pivot) 
        { 
            i+=3;    // En kucuk elemanin indisini artir 
            swap(&arr[i], &arr[j]);
            swap(&arr[i+1],&arr[j+1]);
            swap(&arr[i+2],&arr[j+2]);
        } 
    } 
    swap(&arr[i + 3], &arr[high]);
    swap(&arr[i + 3 + 1], &arr[high + 1]);
    swap(&arr[i + 3 + 2], &arr[high + 2]);
    return (i + 3); 
} 
  
void quickSort(float arr[], int low, int high) 
{ 
    if (low < high)
    { 
        
        float pi = partition(arr, low, high); 
  
        quickSort(arr, low, pi - 3); 
        quickSort(arr, pi + 3, high); 
    } 
} 

int main(){
	
	cout<<endl<<setw(35)<<"Process Started"<<endl;
	cout<<endl<<setw(39)<<GetTime()<<endl<<endl<<endl;
	cout<<setw(46)<<"Process in Progress, please wait..."<<endl;
	
	string sequence_arrays[5000];
	ifstream sequencefile("Sequences//5K_Sequence.fasta");
	
	string temp;
	int count=0;
	
	getline(sequencefile,temp);	
	while(!sequencefile.eof()){
		getline(sequencefile,temp);
		getline(sequencefile,temp);	
		getline(sequencefile,sequence_arrays[count]);
		if(count==4999){
			count++;
			break;
		}
		count++;
	}
	sequencefile.close();
	
	int scores_length=4999*2500*3;
	float *scores=new float[scores_length];
	
	omp_set_num_threads(25);
	
	int max_scores_length=5000/1000*60;
	float *max_scores=new float[max_scores_length];
	
	int max_scores_count=0;
	int scores_count;
	
	int loop_count=5000/1000;
	
	for(int a=0;a<loop_count;a++){
		scores_count=0;
		#pragma omp parallel for schedule(static,5)
		for(int i=a*1000;i<a*1000+999;i++){
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
		#pragma omp barrier
		
		quickSort(scores,0,scores_count*3-3);
		
		for(int i=scores_count*3-3;i>scores_count*3-63;i-=3){
			max_scores[max_scores_count*3] = scores[i];
			max_scores[max_scores_count*3+1] = scores[i+1];
			max_scores[max_scores_count*3+2] = scores[i+2];
			max_scores_count++;
		}
			
	}
	
	quickSort(max_scores,0,max_scores_count*3-3);

	ofstream result_file("ParalelResults.txt");
	
	result_file<<endl<<setw(70)<<"SKOR TABLOSU"<<endl<<endl<<endl;
    result_file<<setw(47)<<"No"<<setw(10)<<"S1"<<setw(10)<<"S2"<<setw(15)<<"Skor"<<endl;
    result_file<<setw(86)<<"--------------------------------------------"<<endl;
	count=1;
	for(int i=max_scores_count*3-3;i>max_scores_count*3-63;i-=3){
		result_file<<setw(47)<<count<<setw(10)<<max_scores[i+1]<<setw(10)<<max_scores[i + 2]<<setw(17)<<max_scores[i]<<endl;
		count++;
	}
	result_file.close();
	
	cout<<endl<<endl<<endl<<setw(34)<<"Process Done"<<endl;
	cout<<endl<<setw(39)<<GetTime()<<endl;
	
	return 0;
}
