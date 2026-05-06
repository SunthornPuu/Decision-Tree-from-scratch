//decision_tree

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
        int property_index = -1;
        double property_value = -1;
};

class DecisionTree{
        private:
                int N,M;
                // N is row_count  and M is columns count
                vector<vector<double>> X;
                vector<double> y;
                int M_depth,m_splits;
                Node root;
                int resort(int l,int r,int feature_index,double feature_value ){
                        vector<pair<double,vector<double>>> resorted(r-l);
                        for(int i=l;i<r;i++)resorted[i-l] =  mp(X[i][feature_index],X[i]);
                        sort(resorted.begin(),resorted.end());
                        for(int i=l;i<r;i++)X[i] = resorted[i-l].s;
                        int matched = 0;
                        while(l<r){
                                int m = (l+r)/2;
                                if(X[m][feature_index]<=feature_value)matched=m,l=m+1;
                                else r=m-1;
                        }
                        return matched;                
                }

                void construct(Node &node, int l, int r,int depth){
                        int val = 0;
                        for(int i=l;i<r;i++)val += double(y[i]);
                        val /= double(r-l);
                        node.value = val;
                        if(depth>=M_depth)return;
                        Node left,right;
                        id best_split = mp(0,0);
                        double most_reduction = INT_MAX;
                        for(int m=0;m<M;m++){
                                for(int i=l;i<r;i++){
                                        //first calculate the mean of group 1 nad 2
                                        //noted that group1 has x less than the set one
                                        double mean1 = 0, mean2 = 0;
                                        int c1 = 0, c2 = 0;
                                        for(int j=l;j<r;j++){
                                                if(X[j][m]<X[i][m])c1++,mean1+=y[j];
                                                else c2++,mean2+=y[j];
                                        }
                                        mean1/=double(c1);
                                        mean2/=double(c2);
                                        if(c1<m_splits||c2<m_splits)continue;
                                        double var1=0,var2=0;
                                        for(int j=l;j<r;j++){  
                                                if(X[j][m]<=X[i][m])var1+=pow(y[j]-var1,2);
                                                else var2+=pow(y[j]-var2,2);
                                        }
                                        if(max(var1,var2)<=most_reduction)
                                                best_split = mp(m,X[i][m]), most_reduction = max(var1,var2);
                                }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
                        }
                        if(best_split.f==-1)return;
                        int split_index = resort(l,r,best_split.f,best_split.s);
                        construct(left,l,split_index,depth+1);
                        construct(right,split_index,r,depth+1);
                        node.left = &left;
                        node.right = &right;
                        node.property_index = best_split.f;
                        node.property_value = best_split.s;
                }

                double query(vector<double> input,Node* node){
                        if(node->property_index == -1)return node->value;
                        if(input[node->property_index] <= node->property_value)query(input,node->left);
                        else query(input,node->right);
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

                double predict(vector<double> test){
                        return query(test,&root);
                }

};