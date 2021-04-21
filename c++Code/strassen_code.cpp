# include <cstdio>
# include <cmath>
# include <iostream>
# include <string>
# include <vector>
# include <ctime>
# include <iomanip>
using namespace std; 


vector<vector <float>> mat_mul(vector<vector<float> > left, vector<vector<float> > right){
    
    vector<vector<float>> result;
    int size = left.size();
    for(int i =0 ;i<size;i++){
        vector<float> row;
        for(int j = 0; j < size; j++){ 
            float val=0;
            for(int k = 0; k<size;k++){
                val += left[i][k]*right[k][j];
            }
            row.push_back(val);
        }
        result.push_back(row);
    }

    return result;
}

vector<vector <float>> strassen(vector<vector<float> > left, vector<vector<float> > right){
    
    vector<vector<float>> result;
    int size = left.size();

    if(size==1){
        //base case
        result = mat_mul(left,right);
        return result;
    }

    bool padded=false;

    if(size%2!=0){
        //perform padding when the dimension is not even
        padded=true;
        int original_size=left.size();
        size+=1;

        left.push_back(vector<float> (size,0));
        right.push_back(vector<float> (size,0));
    }

    int mid = size/2;
    

    //result = mat_mul(left,right);

    return result;
}



int main(int argc, char *argv[]){
    char *flag = argv[1];
    char *dimension = argv[2];
    char *input_file = argv[3];

    int flag_val =atoi(flag);
    int dim = atoi(dimension);

    std::vector< std::vector<float> > vec1{ {1,2,3},{4,5,6},{7,8,9}};
    std::cout << "vec size = " << vec1.size() << "x" << vec1[0].size() << std::endl;

    vector<vector <float>> C;

    C = strassen(vec1,vec1);

    int size = C.size();

    for(int i = 0; i<size;i++){
        for (int j=0;j<size;j++){
            printf("%.2f ",C[i][j]);
        }
        printf("\n");
    }
}
