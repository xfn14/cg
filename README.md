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

## Images

<img src="https://github.com/xfn14/cg/blob/bd83229b35a84c4ae4a331ebb932b14b64611915/resources/tests/test4/4_7.png"  width="600" height="600">
<img src="https://github.com/xfn14/cg/blob/8631832083526717addc74538fc35af16442f593/resources/tests/test3/sistemaSolar.png"  width="600" height="600">

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
