#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}

int main(int argc, char** argv)
{
	FILE *a, *b, *c, *d,*saida;
	Endereco ea, eb, ec, ed;
    int qt=4; int k=0;
	a = fopen("cep_a.dat","rb");
	b = fopen("cep_b.dat","rb");
    c = fopen("cep_c.dat","rb");
    d = fopen("cep_d.dat","rb");
	saida1 = fopen("saida1.dat","wb");
    saida2 = fopen("saida2.dat","wb");
    saidaFinal = fopen("saidaFinal.dat","wb");

	fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);
    fread(&ec,sizeof(Endereco),1,c);
    fread(&ed,sizeof(Endereco),1,d);

	// eof -> End Of File
    
    
    while(k<qt){
    
	while(!feof(a) && !feof(b) && !feof(c) && !feof(d) )
	{
		if(compara(&ea,&eb)<0) // ea < eb
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else // ea >= eb
		{
			fwrite(&eb,sizeof(Endereco),1,saida1);
			fread(&eb,sizeof(Endereco),1,b);
		}

        if(compara(&ec,&ed)<0) // ec < ed
        {
            fwrite(&ec,sizeof(Endereco),1,saida2);
            fread(&ec,sizeof(Endereco),1,c);
        }
        else // ec >= ed
        {
            fwrite(&ed,sizeof(Endereco),1,saida2);
            fread(&ed,sizeof(Endereco),1,d);
        }
    k++;
	}

	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,saida);
		fread(&ea,sizeof(Endereco),1,a);		
	}
	
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,saida);
		fread(&eb,sizeof(Endereco),1,b);		
	}
}
	fclose(a);
	fclose(b);
	fclose(saida);
}

