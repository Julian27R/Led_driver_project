import os

DEVICE_PATH = "/dev/leddev"

def write_led(value):
    try:
        with open(DEVICE_PATH, 'w') as f:
            f.write(value)
        print(f"✅ LED {'ENCENDIDO' if value == '1' else 'APAGADO'}")
    except Exception as e:
        print(f"❌ Error al escribir en el dispositivo: {e}")

def read_led_state():
    try:
        with open(DEVICE_PATH, 'r') as f:
            state = f.read().strip()
        print(f"🔎 Estado actual del LED: {'ENCENDIDO' if state == '1' else 'APAGADO'}")
    except Exception as e:
        print(f"❌ Error al leer el estado del LED: {e}")

def menu():
    print("\n=== CONTROL DE LED POR GPIO ===")
    print("1. Encender LED")
    print("2. Apagar LED")
    print("3. Leer estado actual")
    print("4. Salir")

    while True:
        option = input("Selecciona una opción: ")
        if option == '1':
            write_led('1')
        elif option == '2':
            write_led('0')
        elif option == '3':
            read_led_state()
        elif option == '4':
            print("👋 Saliendo...")
            break
        else:
            print("❗ Opción inválida. Intenta nuevamente.")

if __name__ == "__main__":
    if not os.path.exists(DEVICE_PATH):
        print(f"⚠️ El dispositivo {DEVICE_PATH} no existe. ¿Cargaste el módulo y creaste el nodo con mknod?")
    else:
        menu()

