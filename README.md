
# ExpressCpp

ExpressCpp est un framework backend C++ léger et moderne inspiré par Express.js, conçu pour créer des applications web et des API RESTful de manière simple et efficace.

## 🚀 Caractéristiques

- Architecture légère et performante
- API intuitive similaire à Express.js
- Support des routes HTTP modernes
- Gestion des middlewares
- Intégration JSON native avec nlohmann_json
- Installation simple via vcpkg

## 📋 Prérequis

- Compilateur C++ supportant C++23
- CMake 3.30 ou supérieur
- vcpkg package manager
- Variable d'environnement VCPKG_ROOT configurée
- Git

## 🔧 Dépendances

- [Crow](https://github.com/CrowCpp/Crow) - Framework web C++
- [nlohmann_json](https://github.com/nlohmann/json) - Bibliothèque JSON moderne pour C++

## 🛠 Installation

### 1. Installation des dépendances via vcpkg

```bash
  vcpkg install crow:x64-linux # Adaptez la triplet selon votre système 
  vcpkg install nlohmann-json:x64-linux
```

### 2. Configuration du projet

```bash
  git clone [https://github.com/votre-username/expresscpp.git](https://github.com/votre-username/expresscpp.git)
  cd expresscpp
  mkdir build && cd build
```

# Configuration avec CMake
```bash
  cmake .. -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
```
