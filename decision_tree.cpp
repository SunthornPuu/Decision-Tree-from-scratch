#include "formula.cpp"
#include "vector"
#include "algorithm"
using namespace std;
#define dd pair<double,double>
#define id pair<int,double>
#define f first
#define s second
#define mp make_pair

struct Node{
        double value = -1;
        Node* left = nullptr;
        Node* right = nullptr;
        int property_index,property_value;
};

class DecisionTree{
        private:
                int N,M;
                // N is row_count  and M is columns count
                vector<vector<double>> X;
                vector<double> y;
                int M_depth,m_splits;
                Node root;
                void construct(Node node, int l, int r,int depth){
                        int val = 0;
                        for(int i=l;i<r;i++)val += double(y[i]);
                        val /= double(r-l);
                        if(depth>=M_depth)return;
                        Node left,right;
                        dd best_split = mp(0,0);
                        double most_reduction = INT_MAX;
                        for(int m=0;m<M;m++){
                                vector<id> result(N);
                                for(int i=0;i<N;i++)result[i]=mp(X[m][i],y[i]);
                                sort(result.begin(),result.end());
                        }
                }
        public:
                DecisionTree(vector<vector<double>> given_set, int max_depth = 999999, int min_samples_split = 1){
                        N = given_set.size();
                        M = given_set[0].size()-1;
                        X.resize(N);
                        M_depth = max_depth;
                        m_splits = min_samples_split;
                        for(int i=0;i<N;i++){
                                X[i] = given_set[i];
                                y[i] = given_set[i][M];
                        }
                        construct(root,0,N-1,1);
                }

};

int main(){

}