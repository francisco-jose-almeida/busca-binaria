# Algoritmo de Busca em Árvore Binária

## Introdução
Existem coisas que um computador consegue fazer mais facilmente que um humano, alternativamente, existem operações trivial para um humano que se tornam dificeis para uma máquina. Um exemplo dessas é a busca de algo em uma lista ordenada. Existem muitos algoritmos para realizar essa busca, porém uma das mais eficientes é a **Busca em Árvore Binária**. Esse projeto consistem em uma implementação desta em linguagem C com uma visualização do funcionamento utilizando Raylib.

## Preparando
Para executar o projeto é necessário que o Raylib esteja instalado na sua máquina. Para instalar no linux você precisa previamente do GCC (ou alternativo C99), make e git. [Mais informações aqui](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).

### Para Windows
E recomendado usar  o MinGW-W64, [disponível aqui](https://github.com/skeeto/w64devkit/), baixe e extraia o arquivo *w64devkit.zip*, ele oferece um terminal pronto para usar, utilize esse terminal para compilar o codigo.
Para compilar utilize
```sh
gcc -o raylib_basic_window.exe raylib_basic_window.c -Iinclude -Llib -lraylib -lgdi32 -lwinmm
```
e execute com
```sh
./raylibhelloworld.exe
```
### Para Linux

#### Ubuntu - Debian
```sh
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

#### Fedora
```sh
sudo dnf install alsa-lib-devel mesa-libGL-devel libX11-devel libXrandr-devel libXi-devel libXcursor-devel libXinerama-devel libatomic
```

#### Arch Linux
```sh
sudo pacman -S alsa-lib mesa libx11 libxrandr libxi libxcursor libxinerama
```
Compile o Raylib na sua máquina usando o make
```sh
git clone --depth 1 https://github.com/raysan5/raylib.git raylib
cd raylib/src/
make PLATFORM=PLATFORM_DESKTOP
make PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=SHARED
```

O Raylib estará pronto para usar no terminal.

## Funcionamento

O Algoritmo de Busca Binária funciona percorrendo uma arvore binária partindo da raiz que é o elemento exatamente no meio do vetor(K[i]), calculado como a media entre o limite superior(u) e o limite inferior(l)
i=(u+l)/2
Caso o valor K[i] seja menor que 

## Referências
- Knuth, Donald E. The Art of Computer Programming Volume 3, Cap. 6, Addison-Wesley Longman, 1989.
