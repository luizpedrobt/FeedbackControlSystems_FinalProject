import serial
import threading
import time
import sys
import os

SERIAL_PORT = '/dev/ttyACM1'
BAUD_RATE = 115200

running = True

estados = ["NONE", "IDLE", "HEAT", "COOL", "CONTROL"]

def read_serial(ser):
    while running:
        try:
            if ser.in_waiting >= 5:
                data = ser.read(5)
                if len(data) != 5:
                    continue  # ignora pacotes incompletos

                state, temperature, control, setpoint, peripheral = data[0], data[1], data[2], data[3], data[4]
                estado_str = estados[state] if 0 <= state < len(estados) else f"Desconhecido ({state})"
                print(f"\n[Recebido] Estado: {estado_str}\nTemperatura: {temperature}°C\nVentoinha: {control} %\nSetpoint: {setpoint}°C")

                if peripheral == 0:
                    print(f"Ventoinha: OFF\nAquecedor: OFF\n")
                          
                elif peripheral == 1:
                    print(f"Ventoinha: OFF\nAquecedor: ON\n")
                          
                elif peripheral == 2:
                    print(f"Ventoinha: ON\nAquecedor: OFF\n")
                          
                else:
                    print(f"Ventoinha: ON\nAquecedor: ON\n")

                print("Comando: ", end="", flush=True) 
        except Exception as e:
            print(f"\nErro na leitura: {e}")
            break

def send_commands(ser):
    global running
    print("\n--- Modo de Comando ---")
    print("Digite dois números (comando e valor) ou 'sair' para encerrar.")
    print("Exemplo: 4 25 (modo CONTROL com setpoint 25)\n")

    while running:
        try:
            user_input = input("Comando: ")
            if user_input.lower() in ['sair', 'exit', 'q']:
                running = False
                break

            parts = user_input.strip().split()
            if len(parts) != 2:
                print("Erro: digite dois números separados por espaço.")
                continue

            cmd = int(parts[0])
            val = int(parts[1])

            if 0 <= cmd <= 255 and 0 <= val <= 255:
                ser.write(bytes([cmd, val]))
            else:
                print("Erro: valores devem estar entre 0 e 255.")
        except ValueError:
            print("Erro: entrada inválida.")
        except Exception as e:
            print(f"Erro ao enviar: {e}")
            break

def main():
    global running
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    except serial.SerialException as e:
        print(f"Erro ao abrir {SERIAL_PORT}: {e}")
        sys.exit(1)

    print(f"Conectado em {SERIAL_PORT} a {BAUD_RATE} bps.")

    # Inicia thread de leitura
    read_thread = threading.Thread(target=read_serial, args=(ser,), daemon=True)
    read_thread.start()

    # Entrada de comando
    send_commands(ser)

    print("\nEncerrando...")
    ser.close()

if __name__ == "__main__":
    main()
