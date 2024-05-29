import socket
from twilio.rest import Client

# Server configuration
HOST = '0.0.0.0'  # Use '0.0.0.0' to accept connections from any IP address
PORT = 8080

# Twilio credentials
account_sid = 'xxx'
auth_token = 'xxx'
twilio_phone_number = 'whatsapp:+xxx'
your_phone_number = 'whatsapp:+xxx'

# Initialize Twilio client
client = Client(account_sid, auth_token)

# Function to send SMS notification
def send_notification(message):
    try:
        message = client.messages.create(
            body=message,
            from_=twilio_phone_number,
            to=your_phone_number
        )
        print("Notification sent successfully.")
    except Exception as e:
        print("Failed to send notification:", e)

# Create a socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Set a timeout for socket
server_socket.settimeout(10)

# Bind the socket to the host and port
server_socket.bind((HOST, PORT))

# Start listening for incoming connections
server_socket.listen()

print(f"Server listening on {HOST}:{PORT}")

while True:
    try:
        # Accept incoming connection and then save client socket and address
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")

        # Receive data from the client. 1024 is the maximium amount of bytes
        data = client_socket.recv(1024)

        # check if any data is received
        if data:
            # Process the received data
            decoded_data = data.decode()
            print("Received data:", decoded_data)

            # Send a response back to the client
            response = "Seizure alert received and processed"
            client_socket.sendall(response.encode())

            # Send notification to the phone with the received data
            message = f"Message from Saif Ba Madhaf: {decoded_data}"
            send_notification(message)

        # Close the connection when client closes
        client_socket.close()
        
    except socket.timeout:
        # Handle timeout exception
        print("Socket operation timed out")
    except Exception as e:
        print("An error occurred:", e)

