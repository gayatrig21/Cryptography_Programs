#include<bits/stdc++.h>


typedef long long LL;


void extended_Euclidean_algorithm(LL a, LL b, LL &u, LL &v, LL &w, LL &x, LL &y, LL &z){
	
	/* Initialization */
	// 1. equation
	u = 1;	v = 0;	w = a;
	// 2. equation
	x = 0;	y = 1;	z = b;
	
	
	if( w < z ){ // we change the equations' order
		std::swap( u, x );
		std::swap( v, y );
		std::swap( w, z );
	}
	
	
	LL q;
	while( z != 0 ){
		
		q = w / z;
		
		// (1. equation) - q * (2. equation) 
		u -= q*x;
		v -= q*y;
		w -= q*z;
		
		
		// we change the equations' order
		std::swap( u, x );
		std::swap( v, y );
		std::swap( w, z );
	}
}


int main(){
	
	LL a, b, u, v, w, x, y, z;
	
	// --------------------------
	
	printf( "Data input\n" );
	
	printf( "a = " );
	scanf( "%lld", &a );
	
	printf( "b = " );
	scanf( "%lld", &b );
	
	// --------------------------
	
	extended_Euclidean_algorithm(a, b, u, v, w, x, y, z);
	
	// --------------------------
	
	printf( "\nResults:\n" );
	
	printf( "1. equation: (%lld)*(%lld) + (%lld)*(%lld) = %lld\n", a, u, b, v, w );
	printf( "2. equation: (%lld)*(%lld) + (%lld)*(%lld) = %lld\n", a, x, b, y, z );
	
	// --------------------------
	
	return 0;
}