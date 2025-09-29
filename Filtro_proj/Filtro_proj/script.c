#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION


#include <stdio.h>
#include <string.h>
#include "stb_image_write.h"
#include "stb_image.h"



int main()
{
	unsigned char *bytes;	//Valores do red blue green
	int indice = 0;
	int x,y,p;
	int j = 0,i = 0;
	unsigned char r,g,b;	//Red Blue Green
	char ficheiro[20];


		//Validacao se o ficheiro existe
        do
        {
            printf("Indique o nome do ficheiro de imagem que pretende usar (digite sair para sair): ");
            fgets(ficheiro, sizeof(ficheiro), stdin);
            ficheiro[strcspn(ficheiro, "\n")] = '\0';

            if ((_stricmp(ficheiro, "sair") == 0))
                break;	
            else if (fopen(ficheiro, "r") == 0)
                puts("Imagem precisa estar na mesma pasta que o script!");

        } while (fopen(ficheiro, "r") == 0);



		//Receber informacoes de imagem
		bytes = stbi_load(ficheiro, &x, &y, &p, 3);
        if (!bytes)
        {
            puts("Erro ao abrir imagem.");
			return;
        }

		//Passar por todos os valores de rgb de cada pixel
		for (i = 0; i < y; i++)
        {
            for (j = 0; j < x; j+=2)
            {
				indice = (i * x + j) * 3;
                r = bytes[indice];
                g = bytes[indice + 1];
                b = bytes[indice + 2];
				if (g > 0 || b < r)
				{
					bytes[indice] = 212;
					bytes[indice+1] = 212;
					bytes[indice+2] = 212;
				}
            }
        }
		stbi_write_png(ficheiro,x,y,3,bytes,x*3);
		


	puts("Cor da imagem filtrada!");
	return 0;
}
