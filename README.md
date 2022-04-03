# Solar System

Solar System simulation made with OpenGL/GLUT.

## Authors

- [André Vaz](https://xfn14.github.io)
- [João Mendes](https://github.com/joaopsmendes)
- [Laura Rodrigues](https://github.com/Laura-Rodrigues)
- [Luis Fernandes](https://github.com/LuizFernandez)

## Prerequisites

- OpenGL/GLUT

### Debian/Ubuntu

```console
$ sudo apt-get update
$ sudo apt-get install freeglut3-dev
```

## Usage

### Generator

```console
$ ./generator plane <units> <divisions> <filename>
$ ./generator box <units> <divisions> <filename>
$ ./generator cone <radius> <height> <slices> <stacks> <filename>
$ ./generator sphere <radius> <slices> <stacks> <filename>
$ ./generator tronco <radius1> <radius1> <height> <slices> <stacks> <filename>
```

### Engine

```console
$ ./engine <path> <xml_file>
```

#### Keys

- (**&rarr;**) Rotate the camera to the right.
- (**&larr;**) Rotate the camera to the left.
- (**f**) Toggle xyz axis render.
