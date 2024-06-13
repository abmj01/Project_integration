import socket
from twilio.rest import Client
import DatabaseRetriever
import json
import os

# Server configuration
credentials_file = 'smartguard-38b2d-3fab427b893d.json'  # example of file path
login_spreadsheet_id = '1ECCL-Nr28LnLU-2ut3moZnOwGhVUlK7tOe4lue0S1K0'  # example. the ID can be taken from the link to the sheet, ex: https://docs.google.com/spreadsheets/d/<ID>/edit#gid=0
contact_person_spreadsheet_id = '19luoGWYGi5rutMncAIWuV5WIfVZzsL6s7KDC6R8xBQ0'

HOST = '0.0.0.0'  # Use '0.0.0.0' to accept connections from any IP address
PORT = 8080

# Twilio credentials
account_sid = 'AC27dff6c2f67920e8ed27b4a69838a2e0'
auth_token = 'e324de9a7f08800c023abe64af695fdf'
twilio_phone_number = '+17608560477'

# Initialize Twilio client
twilio_client = Client(account_sid, auth_token)

# Create an instance of DatabaseRetriever
api = DatabaseRetriever.DatabaseRetriever(credentials_file, login_spreadsheet_id, contact_person_spreadsheet_id)


def send_notification(message):
    try:
        # Fetch the phone number based on the name

        destination = "+" + message[2:13]

        pos = message.find(" The user ")

        username = message[14:pos]
        print(username)

        api.change_fall_cell(username)

        msg = twilio_client.messages.create(
            body=message,
            from_=twilio_phone_number,
            to=destination
        )
        print("Notification sent successfully.")
    except Exception as e:
        print("Failed to send notification:", e)


def get_info(message):
    try:
        info = api.fetch_info_on_startup(message)
        print(f"Got the info: {info}")
        return info
    except Exception as e:
        print("Failed to get name:", e)


def handle_client(client_socket):
    try:
        # Receive data from the client
        data = client_socket.recv(1024)

        if data:
            # Process the received data
            decoded_data = data.decode()
            print("Received data:", decoded_data)

            # Send a response back to the client
            if decoded_data[0] == "1":
                # Send notification to the phone with the received data
                send_notification(decoded_data[2:])
                response = "Seizure alert received and processed"
            elif decoded_data[0] == "0":
                watch_name = get_info(decoded_data[2:])
                response = watch_name if watch_name else "Info not found"
            else:
                response = "Invalid data format"

            client_socket.sendall(response.encode())
    except Exception as e:
        print("An error occurred while handling client:", e)
    finally:
        client_socket.close()


def start_server():
    # Create a socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    try:
        # Bind the socket to the host and port
        server_socket.bind((HOST, PORT))
        server_socket.listen()
        print(f"Server listening on {HOST}:{PORT}")

        while True:
            try:
                # Accept incoming connection
                client_socket, client_address = server_socket.accept()
                print(f"Connection from {client_address}")

                # Handle the client connection
                handle_client(client_socket)

            except socket.timeout:
                print("Socket operation timed out")
            except Exception as e:
                print("An error occurred while accepting a connection:", e)

    finally:
        server_socket.close()


if __name__ == "__main__":
    start_server()
