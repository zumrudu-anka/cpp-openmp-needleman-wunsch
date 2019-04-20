#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    float gap= -1.832482334;
    cout<<gap;
    float match= 3.621354295;
    float missmatch = -2.451795405;
    ifstream dosya1;
    dosya1.open("5K_Sequence.fasta");
    int count=0;
    string temp[15002];

    while(!dosya1.eof()){
        getline(dosya1,temp[count]);
        count++;
    }

    dosya1.close();

    string sekansx, sekansy;

	double scores[20];
	int index_of_scores=0;
    for(int i=3; i<15001; i+=3){
        sekansx =temp[i];

        for(int j=i+3; j<14998; j+=3){
            sekansy =temp[j];
            float matris [202][202];
            matris[0][0]=0;
            gap= -1.832482334;
            for(int k=1; k<202; k++){
                matris[0][k]= gap;
                gap +=gap;

            }
            gap= -1.832482334;
            for(int k=1; k<202; k++){
                matris[k][0]= gap;
                gap +=gap;
            }
            gap= -1.832482334;

            float x,y,z;
            int p=0;
            for(int k=1; k<202; k++){
                for(int t=1; t<202; t++){
                        y=gap+matris[k][t-1];
                        z=gap+matris[k-1][t];

                    if(sekansx[k]==sekansy[t]){
                        x=match+matris[k-1][t-1];
                    }
                    else{
                         x=missmatch+matris[k-1][t-1];
                    }
                    matris[k][t]=x>=z?(y>=x?y:x):(z>=y?z:y);

                }

            }
            if(index_of_scores < 20){
				scores[index_of_scores] = matris[201][201];
            	index_of_scores++;
			}
            else{
        		double temp = matris[201][201];
        		double max = scores[0];
        		int tempindex = 0;
        		for(int k = 1; k < 20; k++){
        			if(scores[k] > max){
						max = scores[k];
						tempindex = k;
					}
				}
				if(max > matris[201][201]){
					scores[tempindex] = matrix[201][201];
				}
				
			}
            cout<<matris[201][201]<<endl;
        }
    }
    
    ofstream dosya2("sonuclar.txt");
    for(int i=0;i<20;i++){
    	dosya2<<scores[i]<<endl;
	}
    
    return 0;
}
