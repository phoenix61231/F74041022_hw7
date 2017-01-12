#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
  FILE *input;
  int n,count=0,row=0,col=0,edge=0,num,e_tmp=0;
  char tmp;

  input = fopen("in.txt","r");

  if(input == NULL){
	   printf("Open Failure");
	    return 1;
  }
  fscanf(input,"%d%c",&n,&tmp);
	int mat[n][n];
	while(fscanf(input,"%d%c",&mat[row][col],&tmp)!=EOF){
    if(mat[row][col]!=0) edge++;

    if(col==n-1){
			col=0;
			row++;
		}
		else col++;
  }

  int Et[n],Lt[n],e[edge],l[edge],slack[edge];
  //Et
  for(col=0;col<n;col++){
    Et[col]=mat[0][col];
    if(Et[col]!=0) count++;
  }
  e_tmp=count;
  for(col=count+1;col<n;col++){
    for(row=1;row<n;row++){
      if(mat[row][col]!=0 && (mat[row][col]+Et[row])>Et[col]){
        Et[col]=mat[row][col]+Et[row];
        //printf("%d ",Et[col]);
      }
    }
  }
  //e
  for(row=0;row<count;row++){
    e[row]=0;
  }
  for(row=0;row<n;row++){
    for(col=0;col<n;col++){
      if(mat[row][col]!=0 && e_tmp!=edge){
        e[e_tmp]=Et[col];
        e_tmp++;
      }
    }
  }

  //Lt
  /*for(row=0;row<n-1;row++){
    if(Et[row+1]>Et[row]) Lt[n-1]=Et[row+1];
    else Lt[n-1]=Et[row];
  }*/
  Lt[n-1]=Et[n-1];
  for(row=n-2;row>0;row--){
    for(col=n-1;col>0;col--){
      if(mat[row][col]!=0){
        Lt[row]=Lt[col];
        break;
      }
    }
    //printf("Lt[%d] = %d\n",col,Lt[col]);
    num=Lt[col];
    for(col=n-1;col>0;col--){
      if(mat[row][col]!=0 && mat[row][col]<num){
        num = mat[row][col];
      }
    }
    Lt[row]=Lt[row]-num;
    //printf("Lt[%d] = %d\n\n",row,Lt[row]);
  }

  Lt[0]=0;
  count =0;
  //l
  for(row=0;row<n;row++){
    for(col=0;col<n;col++){
      if(mat[row][col]!=0){
        l[count]=Lt[col]-mat[row][col];
        //printf("%d\n",l[count]);
        count++;
      }
    }
  }
  printf("   a     early_time     late_time     slack\n");
  for(row=0;row<edge;row++){
  printf("a[%3d]      %3d            %3d         %3d\n",row,e[row],l[row],l[row]-e[row]);
  }

  fclose(input);
  return 0;
}
