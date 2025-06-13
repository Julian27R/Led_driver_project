# LED GPIO Driver – Embedded Linux 2025-1S

## Autores

Julian Felipe Gutierrez Ramirez - 1193577237

Felipe Idárraga Quintero - 1002632670

Este proyecto implementa un **driver de dispositivo de carácter para Linux** que permite controlar un **LED físico conectado a un GPIO**, además de una aplicación en **Python** que interactúa con el driver desde el espacio de usuario.

---

## Objetivos

- Comprender el desarrollo de módulos del kernel en Linux
- Manipular pines GPIO desde el kernel
- Registrar un dispositivo de carácter y exponerlo vía `/dev`
- Diseñar una aplicación de usuario (CLI) en Python
- Probar la comunicación entre kernel y user-space

---

## 📦 Estructura del proyecto

led_driver_project/

├── driver/ # Módulo del kernel (.c, Makefile)

├── user_app/ # Aplicación Python (led_control.py)

├── test/ # Evidencia de funcionamiento (logs, fotos, etc.)

└── README.md # Documentación del proyecto

---

## ⚙️ Instrucciones de uso

### 🔧 1. Compilar el módulo
```c
cd driver

make
```
### 2. Liberar manueamente el GPIO
Se libera el GPIO113 manualmente, debido a que ya se habia usado para el servicio de un Heartbeat.
```c
ls /sys-class/gpio | grep 113  "Esto se utuliza para verificar si el GPIO113 esta exportado"

echo 113 | sudo tee /sys/class/gpio/unexport  "ESta linea de codigo se utilizo para liberar el pin GPIO113"

```


### 3. Cargar el módulo
```c
sudo insmod led_driver.ko
```

### 4. Verificar el número major

```c
cat /proc/devices | grep leddev

Ejemplo salida: 239 leddev
```
### 5. Crear el archivo en /dev

```c
sudo mknod /dev/leddev c 239 0

sudo chmod 666 /dev/leddev
```
### 6. Ejecutar la app de usuario

```c
cd ../user_app

python3 led_control.py
```
