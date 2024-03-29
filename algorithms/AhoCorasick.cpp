
#define TAM 100010
#define QTAM 1010
#define SUBTAM 2010
 
using namespace std;
 
typedef pair<int,int> ii ;
typedef long long ll ;
typedef long double ld ;
typedef pair<int,ii> pii ;
 
char T[ TAM ] ;
int sig[ TAM ][ 260 ] ;
vector<int> final[ TAM ] ;
int fail[ TAM ] ;
bool enc[ QTAM ] ;
int end ;
 
void init(){
	end = 1 ;
}
 
void add( string s , int idx ){
	int len = s.size() ;
	int nodo = 0 ;
	for(int i = 0; i < len ; i++ ){
		int c = s[ i ] ;
		if( !sig[ nodo ][ c ] ){
			sig[ nodo ][ c ] = end++ ;
		}
		nodo = sig[ nodo ][ c ] ;
	}
	final[ nodo ].push_back( idx ) ;
}
 
void build(){
	queue<int> q ;
	for(int i = 0; i < 260; i++){
		int next = sig[ 0 ][ i ] ;
		if( next ){
			fail[ next ] = 0 ;
			q.push( next ) ;
		}
	}
	
	while( !q.empty() ){
		int nodo = q.front() ; q.pop() ;
		for(int i = 0; i < 260; i++ ){
			int next = sig[ nodo ][ i ] ;
			int rev = sig[ fail[ nodo ] ][ i ] ;
			if( !next ) sig[ nodo ][ i ] = rev ;
			else{
				q.push( next ) ;
				fail[ next ] = rev ;
				for(int j = 0; j < final[ rev ].size(); j++){
				  final[ next ].push_back( final[ rev ][ j ] );
				}
			}
		}
	}
}
 
void search(){
	int len = strlen( T ) ;
	int nodo = 0 ;
	for(int i = 0; i < len; i++){
		int c = T[ i ] ;
		while( nodo != 0 && !sig[ nodo ][ c ] ) nodo = fail[ nodo ] ;
		nodo = sig[ nodo ][ c ] ;
		for(int j = 0; j < final[ nodo ].size(); j++) enc[ final[ nodo ][ j ] ] = true ;
	}
}
 
int main(){
 
	scanf("%s" , T ) ;
	int n ;
	scanf("%d" , &n ) ;
	init() ;
	char s[ SUBTAM ] ;
	for(int i = 0; i < n; i++){
		scanf("%s" , s ) ;
		add( s , i ) ;
	}
	build() ;
	search() ;
	for(int i = 0; i < n; i++) printf("%s\n" , enc[ i ] ? "Y" : "N" ) ;
	return 0 ;
}
