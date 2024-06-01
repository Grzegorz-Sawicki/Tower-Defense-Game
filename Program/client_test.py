import socket
import threading
import time

def send_message_to_server(client_socket, server_ip, server_port):
    try:
        client_socket.connect((server_ip, server_port))
        
        while True:
            message = input("\nEnter the message to send to the server (or 'exit' to quit): ")
            if message.lower() == 'exit':
                break
            
            message_bytes = message.encode('utf-8')
            message_length = len(message_bytes).to_bytes(4, byteorder='big')

            client_socket.sendall(message_length + message_bytes)
    
    except socket.error as e:
        print(f"Socket error: {e}")
    
    finally:
        client_socket.close()

def receive_responses(client_socket, message_list):
    time.sleep(1)
    try:

        while True:
            response_length_bytes = client_socket.recv(4)
            if not response_length_bytes:
                break
            response_length = int.from_bytes(response_length_bytes, byteorder='big')
            response = client_socket.recv(response_length)
            if not response:
                break
            #print('Received from server:', response.decode('utf-8'))
            message_list.append(response.decode('utf-8'))
    except socket.error as e:
        print(f"Socket error while receiving: {e}")
    finally:
        client_socket.close()

if __name__ == "__main__":
    server_ip = '127.0.0.1'  # Replace with your server's IP
    server_port = 53000      # Replace with your server's port
    message_list = []
    
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    send_thread = threading.Thread(target=send_message_to_server, args=(client_socket, server_ip, server_port))
    receive_thread = threading.Thread(target=receive_responses, args=(client_socket, message_list))
    
    send_thread.start()
    receive_thread.start()
    
    send_thread.join()
    receive_thread.join()
    
    for msg in message_list:
        print(msg)
