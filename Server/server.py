import socket
from twilio.rest import Client
import DatabaseRetriever

# Server configuration
credentialsFile = 'smartguard-38b2d-3fab427b893d.json'  # example of file path
loginSpreadsheetId = '1ECCL-Nr28LnLU-2ut3moZnOwGhVUlK7tOe4lue0S1K0'  # example. the ID can be taken from the link to the sheet, ex: https://docs.google.com/spreadsheets/d/<ID>/edit#gid=0
contactPersonSpreadsheetId = '19luoGWYGi5rutMncAIWuV5WIfVZzsL6s7KDC6R8xBQ0'

HOST = '0.0.0.0'  # Use '0.0.0.0' to accept connections from any IP address
PORT = 8080

# Twilio credentials
account_sid = 'AC27dff6c2f67920e8ed27b4a69838a2e0'
auth_token = 'e324de9a7f08800c023abe64af695fdf'
twilio_phone_number = '+17608560477'

# Initialize Twilio client
client = Client(account_sid, auth_token)


# Function to send SMS notification
def send_notification(message):
    try:
        # fetches the phone number based on the name
        container = message.split()

        pos = container.index("has")

        first_name_list = container[2:pos - 1]
        first_name = ''.join(first_name_list)

        last_name = container[pos - 1]

        holder = api.fetch_contact_person_nr_and_username(first_name, last_name).split()

        destination = ''.join(holder[0])
        username = ''.join(holder[1])

        api.change_fall_cell(username)

        message = client.messages.create(
            body=message,
            from_=twilio_phone_number,
            to=destination
        )
        print("Notification sent successfully.")
    except Exception as e:
        print("Failed to send notification:", e)


def get_name(message):
    try:
        name = api.fetch_name(message)
        print(f"Got the name. {name}")
        return name
    except Exception as e:
        print("Failed to get name: ", e)


# Create a socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Set a timeout for socket
server_socket.settimeout(10)

# Bind the socket to the host and port
server_socket.bind((HOST, PORT))

# Start listening for incoming connections
server_socket.listen()

print(f"Server listening on {HOST}:{PORT}")

# Create an instance of DatabaseRetriever
api = DatabaseRetriever.DatabaseRetriever(credentialsFile, loginSpreadsheetId, contactPersonSpreadsheetId)

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
            if decoded_data[0] == "1":
                # Send notification to the phone with the received data
                send_notification(decoded_data[2:])

                response = "Seizure alert received and processed"

                client_socket.sendall(response.encode())
            elif decoded_data[0] == "0":
                watch_name = get_name(decoded_data[2:])

                response = watch_name

                client_socket.sendall(response.encode())

        # Close the connection when client closes
        client_socket.close()

    except socket.timeout:
        # Handle timeout exception
        print("Socket operation timed out")
    except Exception as e:
        print("An error occurred:", e)