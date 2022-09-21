

#include<iostream>
#include<fstream>
#include<cmath>
#include<vector>
#include<cstring>
#include<random>
#include<iomanip>

using namespace std;



#define double long double



//Must reset after edit
const int Width = 25;
const int Depth = 2;
string savePath = "nodes.dat";

//reset not neccesary
const double WeightLearnRate = 1;
const double BiasLearnRate = 0.1;
string dataPath = "train\\train.txt";


bool enableLogging = true;
bool enableOutput = true;

inline double Sigmoid(double x){
	return 1.0 / (1.0 + exp(-x));
}

inline double Activ(double x){
	return Sigmoid(x);
}

inline double DerivActiv(double x){
	return Sigmoid(x) * (1 - Sigmoid(x));
}

struct Neuron{
	double w[Width];
	double b;

	double sum;
	double output;

}Matrix[Depth][Width];

#define InputLayer Matrix[0]
#define OutputLayer Matrix[Depth-1]

inline void InitRand(){
	default_random_engine e;
	uniform_real_distribution<double> u(-1.0, 1.0);
	for(int i=0; i<Depth; i++){
		for(int j=0; j<Width; j++){
			Matrix[i][j].b = u(e);
			for(int k=0; k<Width; k++){
				Matrix[i][j].w[k] = u(e);
			}
		}
	}
	cout<<"Reset Successful"<<endl;
}

inline void Calc(vector<double>&input){ // O(N^3)

	if(enableOutput){
		cout<<"In Calc(input): "<<endl;
		cout<<"Input: "<<endl;
		for(uint32_t i=0; i<input.size(); i++){
			cout<<setw(15)<<input[i];
		}
		cout<<endl;
	}

	for(int j=0; j<Width; j++){
		InputLayer[j].sum = InputLayer[j].b;
		for(uint32_t k=0; k<input.size(); k++){
			InputLayer[j].sum += input[k] * InputLayer[j].w[k];
		}
		InputLayer[j].output = Activ(InputLayer[j].sum);
	}

	for(int i=1; i<Depth; i++){
		for(int j=0; j<Width; j++){
			Matrix[i][j].sum = Matrix[i][j].b;
			for(int k=0; k<Width; k++){
				Matrix[i][j].sum += Matrix[i-1][k].output * Matrix[i][j].w[k];
			}
			Matrix[i][j].output = Activ(Matrix[i][j].sum);
		}
	}

	if(enableOutput){
		if(enableLogging){
			cout<<"Layers: "<<endl;
			for(int i=0; i<Depth; i++){
				for(int j=0; j<Width; j++){
					cout<<setw(15)<<Matrix[i][j].output;
				}
				cout<<endl;
			}
		}
		
		cout<<"Output:"<<endl;
		for(int j=0; j<Width; j++){
			cout<<setw(15)<<OutputLayer[j].output;
		}
		cout<<endl;
	}

}

double dLtdF[Depth][Width]; // dL/dF
inline void Update(vector<double>& input, vector<double>& expto){ // O(N^3), must call Calc first

	if(enableLogging){
		double Loss = 0;
		for(int j=0; j<Width; j++){
			Loss += (expto[j] - OutputLayer[j].output)*(expto[j] - OutputLayer[j].output);
		}
		Loss /= Width;
		cout<<"Loss: "<<Loss<<endl;
	}




	memset(dLtdF, 0, sizeof(dLtdF)); //set 1 to get 0
	for(int j=0; j<Width; j++){
		// L = sum{ (expto - output)^2 }
		// dL / dF = -2(x-F)
		dLtdF[Depth-1][j] = -2.0 * (expto[j] - OutputLayer[j].output) / Width; //deri Loss to Output
	}


	for(int i=Depth-1; i>0; i--){
		for(int j=0; j<Width; j++){
			// calc dF/db
			// dactiv( C + b ) / db = deriActiv( sum ) * deriSum = deriActiv( sum )
			double deltaB = -BiasLearnRate * (DerivActiv(Matrix[i][j].sum) * dLtdF[i][j]);
			Matrix[i][j].b += deltaB;

			// calc dF/dw
			// deriActiv(sum) * deriSum = deriActiv(sum) * lastF
			for(int k=0; k<Width; k++){
				double deltaW = -WeightLearnRate * (DerivActiv(Matrix[i][j].sum) * Matrix[i-1][k].output * dLtdF[i][j]);
				Matrix[i][j].w[k] += deltaW;
			}

			// calc dF/di as next dL/dF
			for(int k=0; k<Width; k++){
				dLtdF[i-1][k] += DerivActiv(Matrix[i][j].sum) * Matrix[i][j].w[k] * dLtdF[i][j];
			}

		}
	}

	//Calc input layer
	for(int j=0; j<Width; j++){
		double deriB = dLtdF[0][j] * DerivActiv(InputLayer[j].sum); // dL / db
		double deltaB = -BiasLearnRate * deriB;
		InputLayer[j].b += deltaB;
		for(int k=0; k<Width; k++){
			double deriW = input[k] * dLtdF[0][j] * DerivActiv(InputLayer[j].sum);
			double deltaW = -WeightLearnRate * deriW;
			InputLayer[j].w[k] += deltaW;
		}
	}
}

inline void WriteNodes(){
	ofstream outFile(savePath);
	for(int i=0; i<Depth; i++){
		for(int j=0; j<Width; j++){
			outFile<<Matrix[i][j].b<<" ";
			for(int k=0; k<Width; k++){
				outFile<<Matrix[i][j].w[k]<<" ";
			}
			outFile<<endl;
		}
	}
	outFile.close();
}

inline void ReadNodes(){
	ifstream inFile(savePath);
	for(int i=0; i<Depth; i++){
		for(int j=0; j<Width; j++){
			inFile>>Matrix[i][j].b;
			for(int k=0; k<Width; k++){
				inFile>>Matrix[i][j].w[k];
			}
		}
	}
	inFile.close();
}

inline void Train(){
	ifstream inFile(dataPath);
	int cnt;inFile>>cnt;
	while(cnt--){
		vector<double> input, expto;

		for(int i=0; i<Width; i++){double solo;inFile>>solo;input.push_back(solo);}
		for(int i=0; i<Width; i++){double solo;inFile>>solo;expto.push_back(solo);}

		if(enableLogging){
			cout<<"Processing input:"<<endl;
			for(int i=0; i<Width; i++){
				cout<<input[i]<<" ";
			}
			cout<<endl<<"Expected output: "<<endl;
			for(int i=0; i<Width; i++){
				cout<<expto[i]<<" ";
			}
			cout<<endl;
		}

		Calc(input);
		Update(input,expto);

		if(enableLogging){
			WriteNodes();
		}

	}
	inFile.close();
}

inline void Solve(){
	vector<double> input;
	cout<<"Input: "<<endl;
	for(int i=0; i<Width; i++){
		double solo;cin>>solo;input.push_back(solo);
	}
	Calc(input);
}

int main(){

	ReadNodes();
	cout<<"train(t), reset(r) or solve(s) ?"<<endl;
	switch(getchar()){
	case 't':
		int epochs;
		cout<<"How Many times?"<<endl;cin>>epochs;
		if(!enableLogging){
			enableOutput = false;
		}
		while(epochs --){
			Train();
		}

		break;
	case 's':
		Solve();
		break;
	case 'r':
		InitRand();
		break;
	default:
		cout<<"Error!"<<endl;
		break;
	}
	WriteNodes();

	return 0;
}
