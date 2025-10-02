#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include "stb_image_write.h"
#include "stb_image.h"

int main()
{
    unsigned char* bytes;
    int x, y, p;
    int indice = 0;
    int i = 0, j = 0;
    unsigned char r, g, b;
    char ficheiro[100];

    // Validação se o ficheiro existe
    do
    {
        printf("Indique o nome do ficheiro de imagem que pretende usar (digite sair para sair): ");
        fgets(ficheiro, sizeof(ficheiro), stdin);
        ficheiro[strcspn(ficheiro, "\n")] = '\0';

        if ((_stricmp(ficheiro, "sair") == 0))
            return 0;

        FILE* f = fopen(ficheiro, "rb");
        if (!f)
        {
            puts("Imagem precisa estar na mesma pasta que o script!");
        }
        else
        {
            fclose(f);
            break;
        }

    } while (1);

    // Receber informações de imagem
    bytes = stbi_load(ficheiro, &x, &y, &p, 3);
    if (!bytes)
    {
        puts("Erro ao abrir imagem.");
        return 1;
    }

    // Passar por todos os valores de rgb de cada pixel
    for (i = 0; i < y; i++)
    {
        for (j = 0; j < x; j++)
        {
            indice = (i * x + j) * 3;
            r = bytes[indice];
            g = bytes[indice + 1];
            b = bytes[indice + 2];

            // Se o pixel NÃO for roxo, transforma em cinzento
            if (!(r > 100 && b > 100 && g < 80))
            {
                bytes[indice] = 212;
                bytes[indice + 1] = 212;
                bytes[indice + 2] = 212;
            }
        }
    }

    // Escrever para um novo ficheiro
    stbi_write_png("saida.png", x, y, 3, bytes, x * 3);
    stbi_image_free(bytes);

    puts("Filtro roxo aplicado com sucesso!");
    return 0;
}
