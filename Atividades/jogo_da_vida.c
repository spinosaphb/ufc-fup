#include <stdio.h>

int main(){
    int linhas,colunas;
    scanf("%d %d",&linhas,&colunas);
    char m[linhas][colunas];
    char m3[linhas][colunas];

    for(int i=0;i<linhas;i++)
        for(int j=0;j<colunas;j++){
            m3[i][j] = 0;
            scanf(" %c",&m[i][j]);
        }

    for(int i=0;i<linhas;i++){ 
        for(int j=0;j<colunas;j++){
            int vizinho =0;
            if(m[i-1][j-1]=='#')
                vizinho++;
            if(m[i+1][j-1]=='#')
                vizinho++;
            if(m[i-1][j+1]=='#')
                vizinho++;
            if(m[i+1][j+1]=='#')
                vizinho++;
            if(m[i-1][j]=='#')
                vizinho++;
            if(m[i+1][j]=='#')
                vizinho++;
            if(m[i][j-1]=='#')
                vizinho++;
            if(m[i][j+1]=='#')
                vizinho++;
            m3[i][j] = (vizinho<2)?'.':(vizinho>3)?'.':(vizinho==3)?'#':m[i][j];   
        }
    }
    for(int i=0;i<linhas;i++)
        for(int j=0;j<colunas;j++)
            if(m3[i][j]!=0)
                m[i][j] = m3[i][j];
    



    printf("------>\n");
    for(int i=0;i<linhas;i++){
        for(int j=0;j<colunas;j++)
            printf("%c",m[i][j]);
        printf("\n");
    }
    
    return 0;
}