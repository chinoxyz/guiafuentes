
int max_x; 
int max_y; 
int tree[1030][1030]; 

int read2(int idx, int idy){ 
	int sum = 0; 
	while (idy > 0){ 
		sum += tree[idx][idy]; 
		idy -= (idy & -idy); 
	} 
	return sum; 
} 
int read(int idx, int idy){ 
	int sum = 0; 
	while (idx > 0){ 
		sum += read2(idx, idy); 
		idx -= (idx & -idx); 
	} 
	return sum; 
} 
void update(int x , int y , int val){ 
	int y1; 
	while (x <= max_x){ 
		y1 = y; 
		while (y1 <= max_y){ 
			tree[x][y1] += val; 
			y1 += (y1 & -y1); 
		} 
		x += (x & -x); 
	} 
}

result = read(x2+1,y2+1); 
if(x1 > 0 && y1 == 0){ 
  result += -read(x1,y2+1); 
}else if(x1 == 0 && y1 > 0){ 
  result += - read(x2+1,y1); 
}else{ 
  result += -read(x1,y2+1) - read(x2+1,y1) + read(x1,y1); 
}
