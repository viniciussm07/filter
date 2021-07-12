### Filter

Programa em C que pode aplicar até 4 tipos de filtros a uma imagem.

Filtros:
* Grayscale (Tons de cinza);
* Reflection (Reflexão);
* Blur (Desfoque);
* Edges (Detecção de bordas);

Funciona apenas com arquivos no formato .bmp

Obs: este programa foi feito no decorrer do curso CS50x disponibilizado gratuitamente pela Harvard University, então o único arquivo dentro deste programa feito inteiramente por mim foi helpers.c.

Uso: 
* -g para Tons de cinza
``` bash
$ ./filter -g infile.bmp outfile.bmp
```
* -r para Reflexão
``` bash
$ ./filter -r infile.bmp outfile.bmp
```
* -b para Desfoque
``` bash
$ ./filter -b infile.bmp outfile.bmp
```
* -e para Detecção de bordas
``` bash
$ ./filter -e infile.bmp outfile.bmp
```
