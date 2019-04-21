#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    float gap= -1.832482334;
    float match= 3.621354295;
    float missmatch = -2.451795405;
    ifstream dosya1;
    dosya1.open("Sequences//5K_Sequence.fasta");
    int count=0;
    
    /*	Dosyanin tum satirlarini bellekte tutmak istersek bu sekilde gezinebiliriz... Goto TumSatirlarTag
	string temp[15002];
	
    while(!dosya1.eof()){
        getline(dosya1,temp[count]);
        count++;
    }
	*/
	
	string sekans_array[5000];
	string templine;
	//	ilk 3 satiri okumuyoruz...
	getline(dosya1,templine);
	getline(dosya1,templine);
	getline(dosya1,templine);
	
	// 4. satirdan itibaren 2 satir bos gecip okuma yapiyoruz boylece bellekte kapladigimiz alani kucuk tutmaya calistik...
	while(!dosya1.eof()){
		getline(dosya1,sekans_array[count]);
		getline(dosya1,templine);
		getline(dosya1,templine);
		count++;
	}
	
    dosya1.close();

    string sekansx, sekansy;

	float scores[60];
	float minvalue_of_scores; 
	int minvalueindex_of_scores;
	int index_of_scores=0;
    /*
    
    Dosyadaki tum satirlari bellekte tutmak istersek bu sekilde gezinme yapabiliriz...
	
	TumSatirlarTag:
	
		for(int i=3; i<15001; i+=3){
	        sekansx = temp[i];
	        for(int j=i+3; j<14998; j+=3){
	            sekansy = temp[j];
	            float matrix[202][202];
	            matris[0][0]=0;
	            gap= -1.832482334;
	            for(int k=1; k<202; k++){
	                matrix[0][k]= gap;
	                gap +=gap;
	
	            }
	            gap= -1.832482334;
	            for(int k=1; k<202; k++){
	                matrix[k][0]= gap;
	                gap +=gap;
	            }
	            gap= -1.832482334;
	
	            float x,y,z;
	            int p=0;
	            for(int k=1; k<202; k++){
	                for(int t=1; t<202; t++){
	                        y=gap+matrix[k][t-1];
	                        z=gap+matrix[k-1][t];
	
	                    if(sekansx[k]==sekansy[t]){
	                        x=match+matrix[k-1][t-1];
	                    }
	                    else{
	                         x=missmatch+matrix[k-1][t-1];
	                    }
	                    matrix[k][t]=x>=z?(y>=x?y:x):(z>=y?z:y);
	
	                }
	
	            }
	            if(index_of_scores < 20){
					scores[index_of_scores] = matrix[201][201];
	            	index_of_scores++;
				}
	            else{
	        		double max = scores[0];
	        		int tempindex = 0;
	        		for(int k = 1; k < 20; k++){
	        			if(scores[k] > max){
							max = scores[k];
							tempindex = k;
						}
					}
					if(max > matrix[201][201]){
						scores[tempindex] = matrix[201][201];
					}
					
				}
	            cout<<matrix[201][201]<<endl;
	        }
	    }
	*/
    
    for(int i = 0; i < 5000; i++){
        sekansx = sekans_array[i];
        for(int j = i + 1; j < 5000; j++){
            sekansy = sekans_array[j];
            float matrix[202][202];
            matrix[0][0] = 0;
            gap= -1.832482334;
            for(int k = 1; k < 202; k++){
                matrix[0][k] = gap;
                gap += gap;

            }
            gap = -1.832482334;
            for(int k = 1; k < 202; k++){
                matrix[k][0] = gap;
                gap += gap;
            }
            gap = -1.832482334;

            float x, y, z;
            for(int k = 1; k < 202; k++){
                for(int t = 1; t < 202; t++){
                        y = gap + matrix[k][t-1];
                        z = gap + matrix[k-1][t];

                    if(sekansx[k] == sekansy[t]){
                        x = match + matrix[k-1][t-1];
                    }
                    else{
                         x = missmatch + matrix[k-1][t-1];
                    }
                    matrix[k][t] = x >= z ? (y >= x ? y : x) : (z >= y ? z : y);

                }

            }
            if(index_of_scores < 20){
				
				scores[index_of_scores * 3] = i;
	            scores[index_of_scores * 3 + 1] = j;
				scores[index_of_scores * 3 + 2] = matrix[201][201];
            	
				index_of_scores++;
				
				// ilk 20 skor degeri hesaplandigi an aralarinda maximum skor degerini belirliyoruz...
				if(index_of_scores == 20){
					minvalue_of_scores = scores[2];
					minvalueindex_of_scores = 0;
					for(int k = 1; k < 20; k++){
						if(scores[k * 3 + 2] < minvalue_of_scores){
							minvalue_of_scores = scores[k * 3 + 2];
							minvalueindex_of_scores = k; 
						}
					}
				}
				
			}
            else{
            	
            	if(minvalue_of_scores < matrix[201][201]){
					
					scores[minvalueindex_of_scores * 3] = i;
					scores[minvalueindex_of_scores * 3 + 1] = j;
					scores[minvalueindex_of_scores * 3 + 2] = matrix[201][201];
				
					minvalue_of_scores = scores[2];
					minvalueindex_of_scores = 0;
					
					for(int k = 1; k < 20; k++){
						if(scores[k * 3 + 2] < minvalue_of_scores){
							minvalue_of_scores = scores[k * 3 + 2];
							minvalueindex_of_scores = k;
						}
					}
				}				
			}
            cout<<matrix[201][201]<<endl;
        }
    }
    
    // Elde ettigimiz sonuclari buyukten kucuge dogru siraliyoruz...
    for(int i = 0; i < 19; i++){
    	for(int j = i + 1; j < 20; j++){
    		if(scores[j * 3 + 2] > scores[i * 3 + 2]){
    			int tempsekansno1 = scores[i * 3];
    			int tempsekansno2 = scores[i * 3 + 1];
    			double tempscore = scores[i * 3 + 2];
				scores[i * 3] = scores[j * 3];
    			scores[i * 3 + 1] = scores[j * 3 + 1];
    			scores[i * 3 + 2] = scores[j * 3 + 2];
    			scores[j * 3]     = tempsekansno1;
    			scores[j * 3 + 1] = tempsekansno2;
    			scores[j * 3 + 2] = tempscore;
    			
			}
		}
	}
    
    ofstream dosya2("sonuclar.txt");
    dosya2<<endl<<setw(70)<<"SKOR TABLOSU"<<endl<<endl<<endl;
    dosya2<<setw(47)<<"No"<<setw(10)<<"S1"<<setw(10)<<"S2"<<setw(15)<<"Skor"<<endl;
    dosya2<<setw(86)<<"--------------------------------------------"<<endl;
	for(int i=0;i<20;i++){
		if(i==19){
			dosya2<<setw(47)<<i<<setw(10)<<scores[i * 3]<<setw(10)<<scores[i * 3 + 1]<<setw(17)<<scores[i * 3 + 2];
		}
		else{
			dosya2<<setw(47)<<i<<setw(10)<<scores[i * 3]<<setw(10)<<scores[i * 3 + 1]<<setw(17)<<scores[i * 3 + 2]<<endl;
		}
		
    }
    dosya2.close();
    
    return 0;
}
