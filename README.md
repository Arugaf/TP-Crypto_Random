# TP-Crypto_Random

## Домашнее задание №4

### 1. Установка

### 1.1 Библиотека OpenSSL

```bash
sudo apt install libssl-dev
```

### 1.2 Скачивание

```bash
git clone https://github.com/Arugaf/TP-Crypto_Random.git
```

### 1.2 Сборка
```bash
cd TP-Crypto_Random
mkdir build && cd build
cmake ..
make
```

ИЛИ

```bash
cd TP-Crypto_Random
g++ main.cpp -o TP-Crypto_Random -lcrypto
```

### 2. Запуск
```bash
./TP-Crypto_Random --file <filename> --numbilets <uint> --parameter <uint>
```
